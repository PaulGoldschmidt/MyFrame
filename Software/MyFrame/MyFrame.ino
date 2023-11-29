/*
 * MyFrame Version 1
 */
 
#include "wifi_info.h"
#include <Arduino.h>
#include <arduino_homekit_server.h>
#include <ESP8266Ping.h>
#include <EEPROM.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

#define ProjectName "MyFrame"

#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__);  // Get free memory

#define warmPin D1
#define coldPin D2
#define LED_OnboardPin 16

bool received_sat = false;
bool received_hue = false;

bool is_on = false;
float current_brightness = 255.0;
float current_temp = 0.0;
float current_sat = 0.0;
float current_hue = 0.0;

unsigned long previousMillis = 0;  // Stores the last time the ping was performed
const long interval = 300000;      // Interval at which to perform the ping (5 minutes)

const char* host = "google.com";
const int httpPort = 80;

const int addrWarmIntensity = 2000;            // EEPROM address for warmIntensity
const int addrColdIntensity = 2000 + sizeof(int);  // EEPROM address for coldIntensity

void setup() {
  int savedWarmIntensity = 0;
  int savedColdIntensity = 0;

  Serial.begin(115200);
  pinMode(LED_OnboardPin, OUTPUT);  // Initialize onboard LED as an output
  pinMode(warmPin, OUTPUT);
  pinMode(coldPin, OUTPUT);
  EEPROM.begin(512);                                  // Emulated EEPROM Size
  EEPROM.get(addrWarmIntensity, savedWarmIntensity);  // Read values from EEPROM
  EEPROM.get(addrColdIntensity, savedColdIntensity);
  EEPROM.end();  // close emulated EEPROM
  Serial.print("Restored Warm Intensity: ");
  Serial.println(savedWarmIntensity);
  Serial.print("Restored Cold Intensity: ");
  Serial.println(savedColdIntensity);
  analogWrite(warmPin, savedWarmIntensity);  // Write the values to the LED pins
  analogWrite(coldPin, savedColdIntensity);
  wifi_connect();                   // in wifi_info.h
  delay(100);
  my_homekit_setup();
  ota_setup();
  digitalWrite(LED_OnboardPin, HIGH);  // Turn the LED off (NodeMCU onboard LED turns off on HIGH)
}

void loop() {
  checkInternetAlive();
  my_homekit_loop();  // check for homekit updates
  if (!WiFi.isConnected()) {
    wifi_connect();
  }
  ArduinoOTA.handle();
  delay(10);
}

// access your HomeKit characteristics defined in my_accessory.c

extern "C" homekit_server_config_t accessory_config;
extern "C" homekit_characteristic_t cha_on;
extern "C" homekit_characteristic_t cha_bright;
extern "C" homekit_characteristic_t cha_color_temperature;


static uint32_t next_heap_millis = 0;

void my_homekit_setup() {
  cha_on.setter = set_on;
  cha_bright.setter = set_bright;
  cha_color_temperature.setter = set_temp;
  arduino_homekit_setup(&accessory_config);
}

void my_homekit_loop() {
  arduino_homekit_loop();
  const uint32_t t = millis();
  if (t > next_heap_millis) {
    // show heap info every 5 seconds
    next_heap_millis = t + 5 * 1000;
    LOG_D("Free heap: %d, HomeKit clients: %d",
          ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
  }
}

void checkInternetAlive() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time a ping was performed

    Serial.print("Connecting to ");
    Serial.println(host);

    WiFiClient client;
    unsigned long startMillis = millis();
    if (!client.connect(host, httpPort)) {
      Serial.println("Connection failed");
      ESP.restart();
    }

    unsigned long endMillis = millis();
    Serial.print("Connected in ");
    Serial.print(endMillis - startMillis);
    Serial.println(" milliseconds");

    client.stop();
  }
}

void ota_setup() {
  ArduinoOTA.setHostname(ProjectName);
  // Uncomment the next line to set a password for OTA updates
  // ArduinoOTA.setPassword("otapassword");

  ArduinoOTA.onStart([]() {
    Serial.println("Start updating");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();
  Serial.println("Ready for OTA updates");
}
