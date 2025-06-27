#include <Adafruit_NeoPixel.h>

#define ONBOARD_LED_PIN  15
#define TOUCH_SENSOR_PIN 23
#define PIN_NEO_PIXEL    16
#define NUM_PIXELS       3

// neopixels code is just here to make sure they're off
Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
    pinMode(ONBOARD_LED_PIN, OUTPUT);
    digitalWrite(ONBOARD_LED_PIN, LOW);
    pinMode(TOUCH_SENSOR_PIN, INPUT_PULLUP);
    NeoPixel.begin();
    NeoPixel.clear();
    NeoPixel.show();
}

void loop() {
    int touchState = digitalRead(TOUCH_SENSOR_PIN);
    digitalWrite(ONBOARD_LED_PIN, touchState);
    delay(1);
}
