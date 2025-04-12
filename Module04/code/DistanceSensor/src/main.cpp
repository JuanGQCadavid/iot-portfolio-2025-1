#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <VL53L0X.h>

// MQTT Setup
const char *ssid = "IT_guys_11";
const char *password = "iotempire";
const char *mqtt_server = "192.168.14.1";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastRead = 0;
VL53L0X sensor;

void setup_wifi()
{

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      client.publish("status", "RFID sensor connected");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200); // Initialize serial communication
  Wire.begin(D3, D4);   // SDA, SCL Pins manuell festlegen
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  sensor.setTimeout(500); // Timeout for distance measurement
  sensor.init();
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  if (millis() - lastRead < 1000)
  {
    return;
  }

  uint16_t distance = sensor.readRangeSingleMillimeters();

  if (sensor.timeoutOccurred())
  {
    Serial.println("Messung: Timeout!");
  }
  else
  {
    Serial.print("Entfernung: ");
    Serial.print(distance);
    Serial.println(" mm");

    char msg[16];
    sprintf(msg, "%u", distance);

    if (distance < 100) {
      client.publish("distancesensor/mm", msg);
      delay(5000);
    }
    
  }

  lastRead = millis();
}