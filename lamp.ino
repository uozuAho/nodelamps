#include <Adafruit_NeoPixel.h>
#include "IRremote.hpp"

#define PIN_IR           D1
#define LED_IR_FEEDBACK  false
#define PIN_NEO_PIXEL    D5
#define NUM_PIXELS       3
#define MAX_BRIGHTNESS   30
#define SERIAL_BAUD      115200

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);
uint level = 0;

void setup() {
    Serial.begin(SERIAL_BAUD);
    NeoPixel.begin();
    IrReceiver.begin(PIN_IR, LED_IR_FEEDBACK);
}

void loop() {
    if (IrReceiver.decode()) {
        IrReceiver.printIRResultShort(&Serial);
        if (IrReceiver.decodedIRData.protocol == NEC) {
            if (IrReceiver.decodedIRData.command == 0x0) {
                if (level < MAX_BRIGHTNESS) {
                    level += 1;
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x1) {
                if (level > 0) {
                    level -= 1;
                }
            }
        }
        IrReceiver.resume();
    }
    for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
        NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, level, 0));
        NeoPixel.show();
    }
}
