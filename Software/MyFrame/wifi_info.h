/*
 * wifi_info.h
 */

#ifndef WIFI_INFO_H_
#define WIFI_INFO_H_
#define LED_OnboardPin           16

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";

void wifi_connect() {
	WiFi.persistent(false);
	WiFi.mode(WIFI_STA);
	WiFi.setAutoReconnect(true);
	WiFi.begin(ssid, password);
	Serial.println("WiFi connecting...");
	while (!WiFi.isConnected()) {
    digitalWrite(LED_OnboardPin, HIGH);
		delay(100);
		Serial.print(".");
    digitalWrite(LED_OnboardPin, LOW);
	}
	Serial.print("\n");
	Serial.printf("WiFi connected, IP: %s\n", WiFi.localIP().toString().c_str());
}

#endif /* WIFI_INFO_H_ */
