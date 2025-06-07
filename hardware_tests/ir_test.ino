#include "IRremote.hpp"

#define IR_RECEIVE_PIN D1
#define ENABLE_LED_FEEDBACK false

void setup() {
    Serial.begin(115200);
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
    if (IrReceiver.decode()) {
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.resume();
    }
}
