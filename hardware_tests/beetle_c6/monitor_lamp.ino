/*
    Behind-monitor lamp with the following features:

    - touch sensor for cycling through pre-programmed light settings
    - OTA updates
    - set RGB levels via HTTP: GET/POST wozmon.local/led?r=10&g=20&b=30
*/

#include <Adafruit_NeoPixel.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include <WiFi.h>


// -----------------------------------------------------------
// config
const char* WIFI_SSID   = "yourssid";
const char* WIFI_PASS   = "yourpassword";
const char* MDNS_NAME   = "wozmon";
const uint  ONBOARD_LED_PIN = 15;
const uint  TOUCH_SENSOR_PIN = 23;
const uint  NEOPX_PIN = 16;
const uint  NEOPX_NUM_PIXELS = 3;
const uint  NEOPX_MAX_BRIGHTNESS = 30;

// -----------------------------------------------------------
// mem
WiFiServer server(80);
Adafruit_NeoPixel NeoPixel(NEOPX_NUM_PIXELS, NEOPX_PIN, NEO_GRB + NEO_KHZ800);
int neoPx_r = 0;
int neoPx_g = 0;
int neoPx_b = 0;
int prevTouchSensorVal = 0;
String httpRequest = "";


// -----------------------------------------------------------
// funcs
void ledOn() {
    digitalWrite(ONBOARD_LED_PIN, HIGH);
}

void ledOff() {
    digitalWrite(ONBOARD_LED_PIN, LOW);
}

int clampNeoPxVal(int newVal) {
    if (newVal < 0) {
        return 0;
    } else if (newVal > NEOPX_MAX_BRIGHTNESS) {
        return NEOPX_MAX_BRIGHTNESS;
    } else {
        return newVal;
    }
}

void setAllNeoPixels(int r, int g, int b) {
    neoPx_r = clampNeoPxVal(r);
    neoPx_g = clampNeoPxVal(g);
    neoPx_b = clampNeoPxVal(b);
}

// parse r,g,b from a request like $host/led?r=10&g=20&b=30
// returns true if successfully parsed
bool parseHttpRgb(const char *request, int *r, int *g, int *b) {
    const char *start = strstr(request, "/led?");
    if (!start) {
        return false;
    }

    const char *r_pos = strstr(start, "r=");
    const char *g_pos = strstr(start, "g=");
    const char *b_pos = strstr(start, "b=");

    if (r_pos && sscanf(r_pos, "r=%d", r) != 1) return false;
    if (g_pos && sscanf(g_pos, "g=%d", g) != 1) return false;
    if (b_pos && sscanf(b_pos, "b=%d", b) != 1) return false;

    return (r_pos && g_pos && b_pos);
}

void handleHttpRgbRequest(const char *request) {
    int r = -1, g = -1, b = -1;
    if (parseHttpRgb(request, &r, &g, &b)) {
        setAllNeoPixels(r, g, b);
    }
}

void handleHttpRequest() {
    WiFiClient client = server.accept();

    if (client) {
        httpRequest = client.readStringUntil('\r');
        handleHttpRgbRequest(httpRequest.c_str());
        client.clear();
        client.print("HTTP/1.1 200 OK");
    }
}

void neoPxUpdate() {
    for (int pixel = 0; pixel < NEOPX_NUM_PIXELS; pixel++) {
        NeoPixel.setPixelColor(pixel, NeoPixel.Color(neoPx_r, neoPx_g, neoPx_b));
        NeoPixel.show();
    }
}

void handleTouchSensor() {
    int val = digitalRead(TOUCH_SENSOR_PIN);
    if (val == 1 && prevTouchSensorVal == 0) {
        // todo: more light settings
        if (neoPx_b > 0) {
            setAllNeoPixels(0, 0, 0);
        } else {
            setAllNeoPixels(20, 20, 10);
        }
    }
    prevTouchSensorVal = val;
}


// -----------------------------------------------------------
// setup
void setupOnboardLed() {
    pinMode(ONBOARD_LED_PIN, OUTPUT);
}

void setupNeoPixels() {
    NeoPixel.begin();
    setAllNeoPixels(0, 0, 0);
    neoPxUpdate();
}

void setupTouchSensor() {
    pinMode(TOUCH_SENSOR_PIN, INPUT_PULLUP);
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

void setup() {
    setupOnboardLed();
    setupTouchSensor();
    setupNeoPixels();
    connectWifi();

    ArduinoOTA.begin();
    MDNS.begin(MDNS_NAME);
    server.begin();
}


// -----------------------------------------------------------
// go
void loop() {
    ArduinoOTA.handle();
    handleHttpRequest();
    handleTouchSensor();
    neoPxUpdate();
    delay(10);
}
