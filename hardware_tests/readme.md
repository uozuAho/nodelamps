# Hardware tests

# Hardware
This hardware used for all these tests.

- NodeMCU ESP8266 CP2102
    - bought here: https://littlebirdelectronics.com.au/products/nodemcu-lua-wifi-board-based-on-esp8266-cp2102-module?_pos=4&_ss=r
    - ESP-12E

```
+----------------------+
|       NodeMCU        |
|                      |
| [A0]           [D0]  |
| [RSV]          [D1]  |
| [RSV]          [D2]  |
| [S3]           [D3]  |
| [S2]           [D4]  |
| [S1]           [3v3] |
| [CMD]          [GND] |
| [SDO]          [D5]  |--> neopixel data
| [CLK]          [D6]  |
| [GND]          [D7]  |
| [3v3]          [D8]  |
| [EN]           [RX]  |
| [RST]          [TX]  |
| [GND]          [GND] |
| [VIN]          [3v3] |             to neopixels (3 LED strip)
|                      |             GND            --->
|   [LED]              |             VIN            --->
|                      |              D5 --470ohm-- --->
| [RST]        [FLASH] |
+----------------------+
        |      |
        +------+
        Micro USB
```

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
- paste the code below into the arduino IDE, upload
- You should see the on-board LED flashing at 0.5Hz

```cpp
void setup() {
    pinMode(16, OUTPUT);
}

void loop() {
    digitalWrite(16, HIGH);
    delay(1000);
    digitalWrite(16, LOW);
    delay(1000);
}
```

# Wifi test
- Set your SSID and password in [wifi_test](./wifi_test.ino)
- paste it into the arduino IDE and upload
- go to the arduino IDE's serial monitor, set to 115200 baud. You should see
  some output

# Neopixel test
- Wire up hardware as per diagram above
- Paste [neopixel test](./neopixel_test.ino) into the Arduino IDE
    - you may need to install the adafruit neopixel library via the Arduino IDE
- upload
- you should see the neopixels changing colours
