# Beetle ESP 32 C6 dev board

# notes
which pins are safe to use? unclear
- [neopixel](https://esp32io.com/tutorials/esp32-neopixel-led-strip)
    - uses GPIO pin 16
- [ir module](https://esp32io.com/tutorials/esp32-ir-remote-control)
    - uses GPIO pin 19

# wiring
```
                 USB C
                +-----+
                |     |
        +-----------------------+
        |       Beetle C6       |
        | [GND]           [BAT] |
 3v3 <--| [3v3]           [GND] |--> GND
        | [4]             [VIN] |--> neopixel power
        | [5]              [17] |
        | [23]             [16] |--> neopixel data
        | [22]             [19] |--> IR module data
        | [21]             [20] |--> touch sensor data
        | [7]               [6] |
        +-----------------------+

to neopixels (3 LED strip)
GND            --->
VIN            --->
16  --470ohm-- --->

to IR module
GND            ---> pin 2
3v3            ---> pin 3
19  --1kohm--  ---> pin 1

to touch sensor
GND            ---> GND
3v3            ---> VCC
20  --1kohm--  ---> OUT
```


# references
- https://wiki.dfrobot.com/SKU_DFR1117_Beetle_ESP32_C6
- https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
