# Hardware

# Parts
- NodeMCU ESP8266 CP2102
    - bought here: https://littlebirdelectronics.com.au/products/nodemcu-lua-wifi-board-based-on-esp8266-cp2102-module?_pos=4&_ss=r
    - ESP-12E
- adafruit neopixels
- [Vishay 38khz IR module](https://www.vishay.com/docs/82476/tssp58p38.pdf)
    - pins 1,2,3 are left to right, looking at bulge side of IR module
- TTP223 touch sensor
    - https://littlebirdelectronics.com.au/products/capacitive-touch-sensor-for-arduino?_pos=1&_ss=r
- resistors: 1x470ohm, 2x1kohm

# notes
- [nodemcu GPIO recommendations](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)
    - safest: D1, D2, D5, D6, D7

# Wiring
```
                +----------------------+
                |       NodeMCU        |
                |                      |
                | [A0]           [D0]  |
                | [RSV]          [D1]  |--> IR module data
                | [RSV]          [D2]  |--> touch sensor data
                | [S3]           [D3]  |
                | [S2]           [D4]  |
                | [S1]           [3v3] |--> IR module power
                | [CMD]          [GND] |--> gnd
                | [SDO]          [D5]  |--> neopixel data
                | [CLK]          [D6]  |
                | [GND]          [D7]  |
                | [3v3]          [D8]  |
                | [EN]           [RX]  |
                | [RST]          [TX]  |
                | [GND]          [GND] |
  neo pwr   <-- | [VIN]          [3v3] |             to neopixels (3 LED strip)
                |                      |             GND            --->
                |   [LED]              |             VIN            --->
                |                      |              D5 --470ohm-- --->
                | [RST]        [FLASH] |
                +----------------------+             to IR module
                        |      |                     GND            ---> pin 2
                        +------+                     3v3            ---> pin 3
                        Micro USB                    D1  --1kohm--  ---> pin 1

                                                     to touch sensor
                                                     GND            ---> GND
                                                     3v3            ---> VCC
                                                     D2  --1kohm--  ---> OUT
```
