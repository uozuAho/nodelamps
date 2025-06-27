#include <Adafruit_NeoPixel.h>

#define PIN_NEO_PIXEL  16
#define NUM_PIXELS     3
#define BRIGHTNESS     30

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
    NeoPixel.begin();
}

void loop() {
    NeoPixel.clear();

    for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
        NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, BRIGHTNESS, 0));
        NeoPixel.show();
        delay(500);
    }

    NeoPixel.clear();
    NeoPixel.show();
    delay(500);

    for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
        NeoPixel.setPixelColor(pixel, NeoPixel.Color(BRIGHTNESS, 0, 0));
    }
    NeoPixel.show();
    delay(500);

    NeoPixel.clear();
    NeoPixel.show();
    delay(500);
}
