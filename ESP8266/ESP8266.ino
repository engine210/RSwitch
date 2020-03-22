#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define GPIO0 0
#define GPIO2 2

ESP8266WebServer server(80);

void setup() {
  pinMode(GPIO0, OUTPUT);
  pinMode(GPIO2, OUTPUT);
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
  
  server.on ("/gpio", []() {
    if (server.arg("api_key") == "****") {
      if (server.arg("action") == "ON") {
        digitalWrite(GPIO0, HIGH);
        digitalWrite(GPIO2, HIGH);
        server.send(200, "application/json", "{\"gpio0\":\"HIGH\",\"gpio2\":\"HIGH\"}");
      } else if (server.arg("action") == "OFF") {
        digitalWrite(GPIO0, LOW);
        digitalWrite(GPIO2, LOW);
        server.send(200, "application/json", "{\"gpio0\":\"LOW\",\"gpio2\":\"LOW\"}");
      } else {
        server.send(200, "text/plain", "Wrong command");
      }
    } else {
      server.send(200, "text/plain", "Authentication failed");
    }
    
  });
  server.on ("/gpio0", []() {
    if (server.arg("api_key") == "****") {
      if (server.arg("action") == "ON") {
        digitalWrite(GPIO0, HIGH);
        server.send(200, "application/json", "{\"gpio0\":\"HIGH\"}");
      } else if (server.arg("action") == "OFF") {
        digitalWrite(GPIO0, LOW);
        server.send(200, "application/json", "{\"gpio0\":\"LOW\"}");
      } else {
        server.send(200, "text/plain", "Wrong command");
      }
    } else {
      server.send(200, "text/plain", "Authentication failed");
    }
  });
  server.on ("/gpio2", []() {
    if (server.arg("api_key") == "****") {
      if (server.arg("action") == "ON") {
        digitalWrite(GPIO2, HIGH);
        server.send(200, "application/json", "{\"gpio2\":\"HIGH\"}");
      } else if (server.arg("action") == "OFF") {
        digitalWrite(GPIO2, LOW);
        server.send(200, "application/json", "{\"gpio2\":\"LOW\"}");
      } else {
        server.send(200, "text/plain", "Wrong command");
      }
    } else {
      server.send(200, "text/plain", "Authentication failed");
    }
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
