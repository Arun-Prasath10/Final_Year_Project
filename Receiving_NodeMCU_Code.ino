#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "OPPO A31";     // Your Wi-Fi SSID
const char* password = "1234t678"; // Your Wi-Fi password
ESP8266WebServer server(80);

int receivedData = 0;

void setup() {
  Serial.begin(9600);
  delay(10);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Define the endpoint to receive data
  server.on("/sendData", HTTP_GET, handleData);
  server.begin();
}

void loop() {
  server.handleClient();

  // Print received data every 2 seconds
  static unsigned long lastPrintTime = 0;
  unsigned long currentTime = millis();
  if (currentTime - lastPrintTime >= 2000) {
    lastPrintTime = currentTime;
    Serial.print("Received data: ");
    
    Serial.println(receivedData);
    Serial1.println(receivedData);
  }
  
}

void handleData() {
  if (server.args()>0) {
    receivedData = server.arg(0).toInt();
  }
  server.send(200, "text/plain", "Data received successfully");
}
