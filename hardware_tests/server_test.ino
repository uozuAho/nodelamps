/*
 * Control the onboard LED from a web browser.
 * Use mDNS to get the IP address.
 */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

const uint  SERIAL_BAUD = 115200;
const uint  LED_PIN     = 16;
const char* WIFI_SSID   = "yourssid";
const char* WIFI_PASS   = "yourpassword";
const char* MDNS_NAME   = "nodelamp";

WiFiServer server(80);

String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<meta name='viewport' "
                "content='width=device-width, initial-scale=1.0'/>"
                "<meta charset='utf-8'>"
                "<style>"
                "body {font-size:140%;} "
                "#main {display: table; margin: auto;  padding: 0 10px 0 10px; } "
                "h2,{text-align:center; } "
                ".button { padding:10px 10px 10px 10px; width:100%; "
                "background-color: #4CAF50; font-size: 120%;}"
                "</style>"
                "<title>LED Control</title>"
                "</head>"
                "<body><div id='main'><h2>LED Control</h2>";
String html_2 = "";
String html_4 = "</div></body></html>";

String request = "";


void ledOn() {
    digitalWrite(LED_PIN, LOW);
}

void ledOff() {
    digitalWrite(LED_PIN, HIGH);
}

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(SERIAL_BAUD);
    delay(100);

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
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

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

void handleRequest(WiFiClient client) {
    request = client.readStringUntil('\r');

    if (request.indexOf("LEDON") > 0)
    {
        ledOn();
    }
    else if (request.indexOf("LEDOFF") > 0)
    {
        ledOff();
    }

    if (digitalRead(LED_PIN) == HIGH)
    {
        html_2 = "<form id='F1' action='LEDOFF'>"
                 "<input class='button' type='submit' value='Turn off the LED' >"
                 "</form><br>";
    }
    else
    {
        html_2 = "<form id='F1' action='LEDON'>"
                 "<input class='button' type='submit' value='Turn on the LED' >"
                 "</form><br>";
    }

    client.flush();

    client.print(header);
    client.print(html_1);
    client.print(html_2);
    client.print(html_4);

    client.stop();
}

void loop()
{
    MDNS.update();
    WiFiClient client = server.available();

    if (client) {
        handleRequest(client);
    }

    delay(1);
}
