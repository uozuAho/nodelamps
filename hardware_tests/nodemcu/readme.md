# Hardware tests

Wire up everything as per the [nodemcu dev board](./nodemcu_dev_board.md).

# Getting started (linux)
- `sudo usermod -a -G dialout $YOUR_USER`
- log out & back in
- install arduino IDE
- file -> preferences -> add boards:
    - copy paste: http://arduino.esp8266.com/stable/package_esp8266com_index.json
- tools -> board -> boards manager -> install esp8266
- plug board in: arduino should detect
- select board ESP-12E

# Hello world: Blink
- Follow getting started
- paste the [blink](./blink.ino) into the arduino IDE, upload
- You should see the on-board LED flashing at 0.5Hz

# Touch sensor
- Similar to above, use touch sensor sketch

# Wifi test
- Set your SSID and password in [wifi_test](./wifi_test.ino)
- paste it into the arduino IDE and upload
- go to the arduino IDE's serial monitor, set to 115200 baud. You should see
  some output

# Neopixel test
- Wire up hardware as per diagram above
- install the adafruit neopixel library via the Arduino IDE
- Paste [neopixel test](./neopixel_test.ino) into the Arduino IDE
- upload
- you should see the neopixels changing colours

# IR module test
- Wire up hardware as per diagram above
- install IRremote library by shirriff and z3to via the Arduino IDE
- Paste [ir test](./ir_test.ino) into the Arduino IDE
- upload
- run the arduino IDE serial monitor at 115200 baud
- point a remote control at the IR module and press buttons
- you should so info printed in the serial monitor

# mDNS test
This isn't really a hardware test, but whatever.

- set in [server test](./server_test.ino):
    - your SSID and password
    - your DNS name (you can leave it as nodelamp)
- upload to nodemcu
- check the serial monitor. You should see an IP address and 'mDNS OK'
- in a terminal, run:
```sh
# this should get a response and show the nodelamp's IP address
ping nodelamp.local
curl http://nodelamp.local/LEDON  # turn the onboard LED on
curl http://nodelamp.local/LEDOFF # turn the onboard LED off
```
- you can also open http://nodelamp.local in a browser and turn the LED on/off
  from there

# OTA updates
- in the arduino IDE, goto tools -> manage libraries
- install the arduinoOTA library
- first flash needs to be via USB - plug in the board
- set your SSID and password in [ota test 1](./ota_test_1.ino), then flash
- there should now be a nodeMCU with a WiFi icon in the boards dropdown - select
  that
- set your SSID and password in [ota test 2](./ota_test_2.ino), copy to the IDE,
  flash. This time the code will go via WiFi. If you have issues with `espota`,
  turn on verbose compile + upload in file -> preferences -> settings. After
  doing this, a second flash worked for me. I was going to copy the commands
  printed in the Arduino IDE and tweak them manually
