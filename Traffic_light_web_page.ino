#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

#define RED_LED     25
#define YELLOW_LED  26
#define GREEN_LED   27

void handleRoot() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 LED Control</title>
</head>
<body>
  <h1>ESP32 3 LED Control</h1>

  <p><a href="/red/on"><button>Red ON</button></a>
     <a href="/red/off"><button>Red OFF</button></a></p>

  <p><a href="/yellow/on"><button>Yellow ON</button></a>
     <a href="/yellow/off"><button>Yellow OFF</button></a></p>

  <p><a href="/green/on"><button>Green ON</button></a>
     <a href="/green/off"><button>Green OFF</button></a></p>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.on("/red/on", []() {
    digitalWrite(RED_LED, HIGH);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/red/off", []() {
    digitalWrite(RED_LED, LOW);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/yellow/on", []() {
    digitalWrite(YELLOW_LED, HIGH);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/yellow/off", []() {
    digitalWrite(YELLOW_LED, LOW);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/green/on", []() {
    digitalWrite(GREEN_LED, HIGH);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/green/off", []() {
    digitalWrite(GREEN_LED, LOW);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  server.handleClient();
}