# Beetle c6 hardware tests

Hardware:
- [beetle c6](https://wiki.dfrobot.com/SKU_DFR1117_Beetle_ESP32_C6)
- bought here: https://littlebirdelectronics.com.au/products/beetle-esp32-c6-mini-development-board-for-wireless-smart-wearable-device?_pos=2&_psq=beetle&_ss=e&_v=1.0

# First connect + blink test
- plug in the board
- open the arduino IDE
- select the beetle in the board dropdown
    - I saw VALTRACK_V4_MFW_ESP3... on /dev/ttyACM0
- the arduino IDE will prompt you to install stuff to support the board
    - this takes a while
- when done, select the board again in the dropdown (it may have changed)
- in tools -> board, select DFRobot FireBeetle 2 ESP32-C6
- in tools, check the settings match step 10 in https://wiki.dfrobot.com/SKU_DFR1117_Beetle_ESP32_C6
    - I just had to change USB CDC on boot to 'enabled'
- flash the [blink](./blink.ino) sketch:
- The blue LED should flash at 1Hz. The green 'CHG' LED keeps flashing, even
  during programming


# WiFi - AP mode
Flash [wifi ap](./wifi_ap.ino), then connect to the wifi network 'yummonet'
with the password 12345678bobbob. Browse to 192.168.4.1 to turn the LED on/off.


# Wifi - client mode
I tried [wifi test](../nodemcu/wifi_test.ino), replacing `#include <ESP8266WiFi.h>`
with `#include <WiFi.h>`. I couldn't get it to connect to my wifi.

**todo** find a beetle/c6 specific wifi test


# references
- [beetle wiki](https://wiki.dfrobot.com/SKU_DFR1117_Beetle_ESP32_C6)
