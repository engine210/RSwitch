#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define OUT_PIN1 2
#define OUT_PIN2 0

ESP8266WebServer server(80);

void setup() {
  pinMode(OUT_PIN1, OUTPUT);
  pinMode(OUT_PIN2, OUTPUT);
  Serial.begin(115200);

  // Connecting to wifi
  WiFi.begin("engine_dorm_2.4GHz", "0220!@#$");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());  // print the ip
  
  server.on ("/sw", HTTP_POST, []() {
    if (server.arg("led") == "ON") {
      digitalWrite(OUT_PIN1, HIGH);
      digitalWrite(OUT_PIN2, HIGH);
    } else {
      digitalWrite(OUT_PIN1, LOW);
      digitalWrite(OUT_PIN2, LOW);
    }
    server.send(200, "text/plain", "");
  });
  server.on ("/sw1", HTTP_POST, []() {
    if (server.arg("led") == "ON") {
      digitalWrite(OUT_PIN1, HIGH);
    } else {
      digitalWrite(OUT_PIN1, LOW);
    }
    server.send(200, "text/plain", "");
  });
  server.on ("/sw2", HTTP_POST, []() {
    if (server.arg("led") == "ON") {
      digitalWrite(OUT_PIN2, HIGH);
    } else {
      digitalWrite(OUT_PIN2, LOW);
    }
    server.send(200, "text/plain", "");
  });
  
  // For page not found
  server.onNotFound([](){
    server.send(404, "text/plain", "404 NOT found!");
  });
  
  server.begin();
}

void loop() {
  server.handleClient();
}
