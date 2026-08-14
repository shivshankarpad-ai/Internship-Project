#include <Arduino.h>
#include <WiFi.h>
#include <Espalexa.h>

// WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Pins
const int led1 = 25;
const int led2 = 26;
const int led3 = 27;
const int led4 = 33;
const int relay = 14;

const int irSensor1 = 13;
const int irSensor2 = 12;

Espalexa espalexa;

// Alexa Callback Functions
void led1Changed(uint8_t b) {
  digitalWrite(led1, b ? HIGH : LOW);
}

void led2Changed(uint8_t b) {
  digitalWrite(led2, b ? HIGH : LOW);
}

void led3Changed(uint8_t b) {
  digitalWrite(led3, b ? HIGH : LOW);
}

void led4Changed(uint8_t b) {
  digitalWrite(led4, b ? HIGH : LOW);
}

void relayChanged(uint8_t b) {
  digitalWrite(relay, b ? HIGH : LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(relay, OUTPUT);

  pinMode(irSensor1, INPUT);
  pinMode(irSensor2, INPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.println(WiFi.localIP());

  // Register Alexa Devices
  espalexa.addDevice("LED One", led1Changed);
  espalexa.addDevice("LED Two", led2Changed);
  espalexa.addDevice("LED Three", led3Changed);
  espalexa.addDevice("LED Four", led4Changed);
  espalexa.addDevice("Main Relay", relayChanged);

  espalexa.begin();
}

void loop() {
  espalexa.loop();

  // IR Sensor Control
  if (digitalRead(irSensor1) == LOW) {
    digitalWrite(led1, HIGH);
  }

  if (digitalRead(irSensor2) == LOW) {
    digitalWrite(led2, HIGH);
  }

  delay(1);
}