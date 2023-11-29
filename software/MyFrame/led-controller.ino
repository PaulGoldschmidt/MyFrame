void set_on(const homekit_value_t v) {
  bool on = v.bool_value;
  cha_on.value.bool_value = on;  //sync the value

  if (on) {
    is_on = true;
    Serial.println("On");
  } else {
    is_on = false;
    Serial.println("Off");
  }
  setLEDs(current_temp, current_brightness);
}

void set_temp(const homekit_value_t v) {
  Serial.print("set_temp, value:");
  int temp = v.int_value;
  cha_color_temperature.value.int_value = temp;  //sync the value

  current_temp = temp;
  Serial.println(current_temp);
  setLEDs(current_temp, current_brightness);
}

void set_bright(const homekit_value_t v) {
  Serial.println("set_bright, value:");
  int bright = v.int_value;
  cha_bright.value.int_value = bright;  //sync the value
  bright = map(bright, 0, 100, 0, 255);
  current_brightness = bright;
  Serial.println(current_brightness);
  setLEDs(current_temp, current_brightness);
}

void setLEDs(int mired, int brightness) {
  if (is_on == true) {
    int warmIntensity = map(mired, 50, 400, 0, brightness);  // Map the warm intensity for the LED controls
    int coldIntensity = map(mired, 50, 400, brightness, 0);
    warmIntensity = (warmIntensity < 0) ? 0 : warmIntensity;  // If variable is smaller then zero, set to zero
    coldIntensity = (coldIntensity < 0) ? 0 : coldIntensity;  // we don't use an unsigned int because of oferv

    Serial.print("Warm Value: ");
    Serial.print(warmIntensity);
    Serial.print(" | Cold Value: ");
    Serial.println(coldIntensity);
    analogWrite(warmPin, warmIntensity);
    analogWrite(coldPin, coldIntensity);
    // Write to EEPROM
    EEPROM.begin(4096);
    EEPROM.put(addrWarmIntensity, warmIntensity);
    EEPROM.put(addrColdIntensity, coldIntensity);
    EEPROM.commit();
    EEPROM.end();
    Serial.print("Written to EEPROM - Warm intensity: ");
    Serial.print(warmIntensity);
    Serial.print(" | Cold intensity: ");
    Serial.println(coldIntensity);
  } else {
    analogWrite(warmPin, 0);
    analogWrite(coldPin, 0);
    // Write to EEPROM
    EEPROM.begin(4096);
    EEPROM.put(addrWarmIntensity, 0);
    EEPROM.put(addrColdIntensity, 0);
    EEPROM.commit();
    EEPROM.end();
  }
}