#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "index.h"

#define OUT_PIN1 2
#define OUT_PIN2 0

const char ssid[] = "engine_dorm_2.4GHz";
const char pass[] = "0220!@#$";

ESP8266WebServer server(80); // Run a web server on port 80

// handaling the request of main page
void rootRouter() {
  server.send (200, "text/html", PAGE_INDEX );
}

void setup() {
  pinMode(OUT_PIN1, OUTPUT);
  pinMode(OUT_PIN2, OUTPUT);
  Serial.begin(115200);

  // Connecting to wifi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());  // print the ip

  // the main page
  server.on ( "/", rootRouter);
  // page for switch 1
  server.on ("/sw1", []() {
     String state = server.arg("led");
     if (state == "ON") {
         digitalWrite(OUT_PIN1, HIGH);
     } else if (state == "OFF") {
         digitalWrite(OUT_PIN1, LOW);
     }
     
     Serial.print("OUT_PIN1: ");
     Serial.println(state);
  });
  // page for switch 2
  server.on ("/sw2", []() {
     String state = server.arg("led");
     if (state == "ON") {
         digitalWrite(OUT_PIN2, HIGH);
     } else if (state == "OFF") {
         digitalWrite(OUT_PIN2, LOW);
     }
     
     Serial.print("OUT_PIN2: ");
     Serial.println(state);
  });
  // For page not found
  server.onNotFound([](){
    server.send(404, "text/plain", "404 NOT found!");
  });
  
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
    server.handleClient(); // handaling requests
}
