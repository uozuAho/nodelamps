# Beetle c6 hardware tests

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
- flash the following sketch:

```cpp
int led = 15;
void setup() {
  pinMode(led,OUTPUT);
}

void loop() {
  digitalWrite(led,HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(500);
}
```

- The blue LED should flash at 1Hz. The green 'CHG' LED keeps flashing, even
  during programming


# references
- [beetle wiki](https://wiki.dfrobot.com/SKU_DFR1117_Beetle_ESP32_C6)
