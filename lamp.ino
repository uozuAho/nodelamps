#include <Adafruit_NeoPixel.h>
#include "IRremote.hpp"

#define IR_PIN                 D1
#define IR_LED_FEEDBACK        false
#define IR_PROTOCOL            NEC
#define IR_CMD_UP              0x0
#define IR_CMD_DOWN            0x1
#define NEOPX_PIN              D5
#define NEOPX_NUM_PIXELS       3
#define NEOPX_MAX_BRIGHTNESS   30
#define SERIAL_BAUD            115200

Adafruit_NeoPixel NeoPixel(NEOPX_NUM_PIXELS, NEOPX_PIN, NEO_GRB + NEO_KHZ800);
uint level = 0;

void setup() {
    Serial.begin(SERIAL_BAUD);
    NeoPixel.begin();
    IrReceiver.begin(IR_PIN, IR_LED_FEEDBACK);
}

void loop() {
    if (IrReceiver.decode()) {
        IrReceiver.printIRResultShort(&Serial);
        if (IrReceiver.decodedIRData.protocol == IR_PROTOCOL) {
            if (IrReceiver.decodedIRData.command == IR_CMD_UP) {
                if (level < NEOPX_MAX_BRIGHTNESS) {
                    level += 1;
                }
            }
            else if (IrReceiver.decodedIRData.command == IR_CMD_DOWN) {
                if (level > 0) {
                    level -= 1;
                }
            }
        }
        IrReceiver.resume();
        Serial.print("level: ");
        Serial.print(level);
        Serial.println();
    }
    for (int pixel = 0; pixel < NEOPX_NUM_PIXELS; pixel++) {
        NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, level, 0));
        NeoPixel.show();
    }
}
