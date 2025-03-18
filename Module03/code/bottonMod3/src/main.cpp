#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "IT_guys_11";
const char* password = "iotempire";

#define EMERGENCY_B D8

// MQTT Broker details
const char* mqtt_server = "192.168.14.1";  // Public broker example
const int mqtt_port = 1883;                     // Default MQTT port

WiFiClient espClient;
PubSubClient client(espClient);

// Callback function (not used in this example)
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);
}

void connectToMqtt() {
  Serial.print("Connecting to MQTT...");
  while (!client.connected()) {
    String clientId = "WemosD1Mini-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected to MQTT broker!");
      client.subscribe("test/topic"); // Subscribe if needed
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Trying again in 5 seconds...");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(EMERGENCY_B, INPUT);

  Serial.begin(115200);

  // Connect to WiFi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Setup MQTT client
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Connect to MQTT broker
  connectToMqtt();
}

void loop() {
  if (!client.connected()) {
    connectToMqtt();
  }

  if (digitalRead(EMERGENCY_B) == HIGH) {
    String message = "HELP!!!!";
    Serial.println(message);
    client.publish("emergency/help", message.c_str());
    delay(1000);
  }

  // client.loop();

}

