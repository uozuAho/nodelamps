#include <Adafruit_NeoPixel.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include <WiFi.h>

const char* WIFI_SSID   = "yourssid";
const char* WIFI_PASS   = "yourpassword";
const char* MDNS_NAME   = "beetle";
const uint  TOUCH_SENSOR_PIN = 23;
const uint  PIN_NEO_PIXEL = 16;
const uint  NUM_PIXELS = 3;
const uint  ONBOARD_LED_PIN = 15;

// neopixels code is just here to make sure they're off
Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void ledOn() {
    digitalWrite(ONBOARD_LED_PIN, LOW);
}

void ledOff() {
    digitalWrite(ONBOARD_LED_PIN, HIGH);
}

bool isLedOn() {
    return digitalRead(ONBOARD_LED_PIN) == LOW;
}

void toggleLed() {
    if (isLedOn()) {
        ledOff();
    } else {
        ledOn();
    }
}

void setupOnboardLed() {
    pinMode(ONBOARD_LED_PIN, OUTPUT);
    ledOff();
}

void setupTouchSensor() {
    pinMode(TOUCH_SENSOR_PIN, INPUT_PULLUP);
}

void setupNeoPixel() {
    NeoPixel.begin();
    NeoPixel.clear();
    NeoPixel.show();
}

void connectWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED)
    {
        ledOn();
        delay(250);
        ledOff();
        delay(250);
    }

    ledOff();
}

void setup()
{
    setupOnboardLed();
    setupTouchSensor();
    setupNeoPixel();
    connectWifi();

    ArduinoOTA.begin();
    MDNS.begin(MDNS_NAME);
}

void loop()
{
    ArduinoOTA.handle();
    toggleLed();
    delay(1000);
}
