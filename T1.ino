#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <ADXL345.h>

const char* ssid = "OPPO A31";      // Your Wi-Fi SSID
const char* password = "1234t678";  // Your Wi-Fi password
const char* host = "192.168.43.18"; // IP address of NodeMCU #2

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(0x1E); // Change to your sensor's I2C address

void setup() {
  Serial.begin(9600);
  delay(100);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize the magnetometer
  if (!mag.begin()) {
    Serial.println("Could not find a valid HMC5883 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  // Read data from the magnetometer
  sensors_event_t event;
  mag.getEvent(&event);

  float heading = atan2(event.magnetic.y, event.magnetic.x);
  if (heading < 0) 
    heading += 2 * PI;

  float headingDegrees = heading * 180 / M_PI;
  
  // Send the heading data to NodeMCU #2
  sendData(String(headingDegrees));

   // Send data every 2 seconds
}

void sendData(String data) {
  Serial.print("Sending data: ");
  Serial.println(data);

  WiFiClient client;
  
  if (client.connect(host, 80)) { 
    client.print("GET /sendData?data=" + data + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    delay(100);
    
    
  }
  
  
}
