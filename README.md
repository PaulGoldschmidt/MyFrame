# HomeKit-Enabled Lightframe 💡

## Description

This project provides a customizable, HomeKit-enabled Lightframe that allows users to adjust the white color temperature seamlessly. Built on the ESP8266 platform, it utilizes the Arduino-Homekit library by Mixiaoxiao (Wang Bin) to interface with Apple's Home app.

## Features

- **HomeKit Integration**: Control your Lightframe using the Apple Home app or Siri 🏠.
- **Adjustable White Temperatures**: Seamlessly switch between cool and warm white tones 💡.
- **Customizable**: Easily tweak the settings for your local environment 🛠.

## Prerequisites

- An ESP8266-based board 👾. 
- Arduino IDE installed on your system 🪄.
- Basic knowledge of electronics and Arduino programming 👀.

## Hardware Setup

### Components

- ESP8266-based board (e.g., NodeMCU, Wemos D1 Mini, etc.)
- LEDs for cold white and warm white colors.

### Connections

- Connect the **Cold White** LED to pin **D1** on the ESP8266.
- Connect the **Warm White** LED to pin **D2** on the ESP8266.

## Software Setup

### Library Installation

1. Download the `Arduino-Homekit` library from [here](/software/libraries/).
2. Install the library into the Arduino IDE:
   - Open the Arduino IDE.
   - Navigate to **Sketch** -> **Include Library** -> **Add .ZIP Library**.
   - Select the downloaded `Arduino-Homekit` library.

### Sketch Setup

1. Navigate to `/software/libraries` and open the provided Arduino sketch.
2. Update the `wifi_info.h` file:
   - Set your local Wi-Fi credentials:
     ```cpp
     const char *ssid = "YOUR_WIFI_SSID";
     const char *password = "YOUR_WIFI_PASSWORD";
     ```
3. Verify and upload the sketch to your ESP8266 board.

## HomeKit Pairing

1. Open the **Home** app on your iOS device.
2. Tap on **Add Accessory**.
3. Scan or enter the setup code: `3333-3333`.

## Usage

Once paired, you can control the Lightframe using the Home app or Siri:
- Turn the Lightframe on/off.
- Adjust the white color temperature between cool and warm tones.

## Support and Contribution

Feel free to [open an issue](/issues) or [submit a pull request](/pulls) if you encounter any problems or want to contribute to this project.

## License

This project is open-source and available under the [GNU GENERAL PUBLIC LICENSE](/LICENSE).

## Acknowledgements

Special thanks to Mixiaoxiao (Wang Bin) for the [Arduino-Homekit](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266) library which made this project possible in the first place.
