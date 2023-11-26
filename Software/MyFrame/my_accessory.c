/*
 * my_accessory.c
 * Define the accessory in C language using the Macro in characteristics.h
 */

#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void my_accessory_identify(homekit_value_t _value) {
  printf("accessory identify\n");
}

homekit_characteristic_t cha_on = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "MyFrame");
homekit_characteristic_t cha_bright = HOMEKIT_CHARACTERISTIC_(BRIGHTNESS, 50);
homekit_characteristic_t cha_color_temperature = HOMEKIT_CHARACTERISTIC_(COLOR_TEMPERATURE, 350);

homekit_accessory_t *accessories[] = {
  HOMEKIT_ACCESSORY(.id = 1, .category = homekit_accessory_category_lightbulb, .services = (homekit_service_t *[]){ HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics = (homekit_characteristic_t *[]){ HOMEKIT_CHARACTERISTIC(NAME, "MyFrame"), HOMEKIT_CHARACTERISTIC(MANUFACTURER, "P3G3"), HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "000001"), HOMEKIT_CHARACTERISTIC(MODEL, "MyFrameAlpha"), HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "6.9"), HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify), NULL }), HOMEKIT_SERVICE(LIGHTBULB, .primary = true, .characteristics = (homekit_characteristic_t *[]){ &cha_on, &cha_name, &cha_bright, &cha_color_temperature, NULL }), NULL }),
  NULL
};

homekit_server_config_t accessory_config = {
  .accessories = accessories,
  .password = "333-33-333"
};