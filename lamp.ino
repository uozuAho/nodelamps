#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
#include "IRremote.hpp"


// -----------------------------------------------------------
// config
#define IR_PIN                 D1
#define IR_LED_FEEDBACK        false
#define IR_PROTOCOL            NEC
#define IR_CMD_UP              0x0
#define IR_CMD_DOWN            0x1
#define NEOPX_PIN              D5
#define NEOPX_NUM_PIXELS       3
#define NEOPX_MAX_BRIGHTNESS   30
#define SERIAL_BAUD            115200
const uint  LED_PIN            = 16;
const char* WIFI_SSID          = "yourssid";
const char* WIFI_PASS          = "yourpassword";
const char* MDNS_NAME          = "nodelamp";

// -----------------------------------------------------------
// mem
WiFiServer server(80);
Adafruit_NeoPixel NeoPixel(NEOPX_NUM_PIXELS, NEOPX_PIN, NEO_GRB + NEO_KHZ800);
int neoPx_r = 0;
int neoPx_g = 0;
int neoPx_b = 0;
String httpRequest = "";
long lastStatusUpdate = 0;


// -----------------------------------------------------------
// funcs
void ledOn() {
    digitalWrite(LED_PIN, LOW);
}

void ledOff() {
    digitalWrite(LED_PIN, HIGH);
}

bool isLedOn() {
    return digitalRead(LED_PIN) == LOW;
}

bool isLedOff() {
    return !isLedOn();
}

int clampLedVal(int newVal) {
    if (newVal < 0) {
        return 0;
    } else if (newVal > NEOPX_MAX_BRIGHTNESS) {
        return NEOPX_MAX_BRIGHTNESS;
    } else {
        return newVal;
    }
}

int incrLedVal(int currentValue, int increment) {
    return clampLedVal(currentValue + increment);
}

void handleIrSignal() {
    if (IrReceiver.decode()) {
        IrReceiver.printIRResultShort(&Serial);
        if (IrReceiver.decodedIRData.protocol == IR_PROTOCOL) {
            if (IrReceiver.decodedIRData.command == IR_CMD_UP) {
                neoPx_r = incrLedVal(neoPx_r, 1);
                neoPx_g = incrLedVal(neoPx_g, 1);
                neoPx_b = incrLedVal(neoPx_b, 1);
            }
            else if (IrReceiver.decodedIRData.command == IR_CMD_DOWN) {
                neoPx_r = incrLedVal(neoPx_r, -1);
                neoPx_g = incrLedVal(neoPx_g, -1);
                neoPx_b = incrLedVal(neoPx_b, -1);
            }
        }
        IrReceiver.resume();
    }
}

// parse r,g,b from a request like localhost/led?r=10&g=20&b=30
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
        neoPx_r = clampLedVal(r);
        neoPx_g = clampLedVal(g);
        neoPx_b = clampLedVal(b);
    }
}

void handleHttpRequest() {
    WiFiClient client = server.available();

    if (client) {
        httpRequest = client.readStringUntil('\r');
        handleHttpRgbRequest(httpRequest.c_str());
        client.flush();
        client.print("HTTP/1.1 200 OK");
    }
}

void neoPxUpdate() {
    for (int pixel = 0; pixel < NEOPX_NUM_PIXELS; pixel++) {
        NeoPixel.setPixelColor(pixel, NeoPixel.Color(neoPx_r, neoPx_g, neoPx_b));
        NeoPixel.show();
    }
}

void printStatus() {
    long now = millis();
    if (now - lastStatusUpdate > 5000) {
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        Serial.print("NeoPixel values (RGB): ");
        Serial.print(neoPx_r);
        Serial.print(" ");
        Serial.print(neoPx_g);
        Serial.print(" ");
        Serial.println(neoPx_b);
        lastStatusUpdate = now;
    }
}


// -----------------------------------------------------------
// go
void setup() {
    pinMode(LED_PIN, OUTPUT);

    Serial.begin(SERIAL_BAUD);
    delay(100);

    NeoPixel.begin();
    IrReceiver.begin(IR_PIN, IR_LED_FEEDBACK);

    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        ledOn();
        delay(250);
        ledOff();
        delay(250);
    }

    ledOff();

    if (!MDNS.begin(MDNS_NAME))
    {
        Serial.println("mDNS setup failed");
    }
    else
    {
        Serial.println("mDNS responder started");
    }

    server.begin();
}

void loop() {
    MDNS.update();
    handleIrSignal();
    handleHttpRequest();
    neoPxUpdate();
    printStatus();
    delay(1);
}
