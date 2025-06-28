# Beetle c6 hardware tests

Hardware:
- [dev board wiring](./beetle_dev_board.md)
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

# Neopixel test
- wire as per [dev board wiring](./beetle_dev_board.md)
- flash [neopixel test](./neopixel_test.ino)

# Touch sensor test
- [touch_sensor_test](./touch_sensor_test.ino)

# WiFi - AP mode
Flash [wifi ap](./wifi_ap.ino), then connect to the wifi network 'yummonet'
with the password 12345678bobbob. Browse to 192.168.4.1 to turn the LED on/off.

# Wifi - client mode
Flash [wifi client](./wifi_client.ino), the open tools -> serial monitor. You
should see messages indicating success/failure to connect to your network.

# mDNS and OTA update test
- enter your SSID and password into [ota_test](./ota_test.ino) and flash via USB
- the onboard LED will flash quickly until WiFi connects, then flash at 0.5Hz
- `ping beetle.local`. You should get a response
- you should now see a new IP address option in the Arduino IDE board drop down
- select the IP address, and re-select DFRobot FireBeetle 2 ESP32-C6
- change the LED flash rate to say 0.25Hz (not too similar to the 'wifi
  connecting' rate), then flash again
    - if/when prompted for password, enter any value

# references
- [beetle wiki](https://wiki.dfrobot.com/SKU_DFR1117_Beetle_ESP32_C6)
