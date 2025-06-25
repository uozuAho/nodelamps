#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

int myLED = 15;
const char* ssid     = "yummonet";
const char* password = "12345678bobbob";

WiFiServer server(80);

void setup() {
  pinMode(myLED, OUTPUT);

  Serial.begin(115200);
  delay(100);

  Serial.println("Configuring access point...");

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // Detect waiting for connection...

  if (client) {                             // Connection detecting
    Serial.println("New Client.");
    String currentLine = "";                // Create a String variable to store data
    while (client.connected()) {            // loop when keep connecting
      if (client.available()) {             // Detect is there is data on the connection
        char c = client.read();             // Read the received data
        //Serial.write(c);                    // Print on serial monitor
        if (c == '\n') {                    // If an newline character  is read

          //Use newline character to indicate the end
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
             //Connect character with here
            client.print("Click <a href=\"/ON\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/OFF\">here</a> to turn OFF the LED.<br>");

            // empty line in a HTTP response
            client.println();
            // Break out of a loop
            break;
          } else {    // Clear cached data in variable if there is one newline character
            currentLine = "";
          }
        } else if (c != '\r') {  // If characters except Carriage Return is obtained
          currentLine += c;      // Add the obtained character to end of the variable
        }

        // Check if /ON or /OFF is obtained
        if (currentLine.endsWith("/ON")) {
          digitalWrite(myLED, HIGH);               //Turn on LED when /ON is obtained
        }
        if (currentLine.endsWith("/OFF")) {
          digitalWrite(myLED, LOW);                //Turn on LED when /OFF is obtained
        }
      }
    }
    // disconnect
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
