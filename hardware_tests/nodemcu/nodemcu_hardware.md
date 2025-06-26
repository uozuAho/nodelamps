# Hardware

# Parts
- NodeMCU ESP8266 CP2102
    - bought here: https://littlebirdelectronics.com.au/products/nodemcu-lua-wifi-board-based-on-esp8266-cp2102-module?_pos=4&_ss=r
    - ESP-12E
- adafruit neopixels
- [Vishay 38khz IR module](https://www.vishay.com/docs/82476/tssp58p38.pdf)
    - pins 1,2,3 are left to right, looking at bulge side of IR module
- resistors: 1x470ohm, 1x1kohm

# Wiring
```
                +----------------------+
                |       NodeMCU        |
                |                      |
                | [A0]           [D0]  |
                | [RSV]          [D1]  |--> IR module data
                | [RSV]          [D2]  |
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
```
