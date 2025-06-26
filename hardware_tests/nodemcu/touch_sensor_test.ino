#define LED_PIN 16
#define TOUCH_SENSOR_PIN D2

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(TOUCH_SENSOR_PIN, INPUT_PULLUP);
    digitalWrite(LED_PIN, LOW);
}

void loop() {
    int touchState = digitalRead(TOUCH_SENSOR_PIN);
    digitalWrite(LED_PIN, touchState);
    delay(1);
}
