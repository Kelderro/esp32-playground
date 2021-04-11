# esp32-playground

## Setting up development environment

### Installation
```curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh```

Please see https://arduino.github.io/arduino-cli/installation/ for more details around the installation of arduino-cli.

## Configuration
By default the ESP32 board is not supported by arduino-cli. Point the arduino-cli configuration to the ESP32 board package via the URL

```arduino-cli config init --additional-urls https://dl.espressif.com/dl/package_esp32_index.json```

If you already have arduino-cli installed this command could result in the following response message ```Config file already exists, use --overwrite to discard the existing one.```. Please check with ```arduino-cli config dump``` if the ```additional_urls``` property contains the esp32 URL (https://dl.espressif.com/dl/package_esp32_index.json). If that is not the case you can the URL via the command ```arduino-cli config add --additional-urls https://dl.espressif.com/dl/package_esp32_index.json```.


### Install platform
```arduino-cli core update-index```

### Install the board to compile the code
```arduino-cli core install esp32:esp32```

### Compile your first sketch
```arduino-cli compile --fqbn esp32:esp32:esp32 ./src/01-blinky```

A more detailed guide of these steps can be found at https://www.survivingwithandroid.com/arduino-cli-compile-upload-manage-libraries-cores-boards/

## ESP32 board
All the sketches in this repository are tested on an ESP32 ESPRESSIF ESP32-WROOM-32 development board. This board is an ESP32 Development Board with 2.4 Ghz WiFi + Bluetooth Ultra Low Power Consumption Dual Cores ESP-32 Board.

## How to get an ESP32 board
On the internet there are multiple ESP32 board suppliers. For this project I bought the [ESP32 Development Board WiFi+bluetooth Ultra Low Power Consumption Dual Cores ESP-32 ESP-32S Board](https://www.banggood.com/ESP32-Development-Board-WiFi+bluetooth-Ultra-Low-Power-Consumption-Dual-Cores-ESP-32-ESP-32S-Board-p-1109512.html) board from Banggood but there are many other suppliers who are selling ESP32 boards, for example Amazon, Ebay and Aliexpress. 

## Other resources
* [Getting started guide from ESPRESSIF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html)
* [ESP32 playlist from Andreas Spiess](https://www.youtube.com/watch?v=jhjZZkKupk8&list=PL3XBzmAj53RnZPeWe799F-uoXERBldhn9)
* [Arduino-esp32 from ESPRESSIF on GitHub](https://github.com/espressif/arduino-esp32)