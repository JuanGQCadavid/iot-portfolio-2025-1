#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
// #include <MFRC522DriverI2C.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>

// Learn more about using SPI/I2C or check the pin assigment for your board: https://github.com/OSSLibraries/Arduino_MFRC522v2#pin-layout
MFRC522DriverPinSimple ss_pin(15);

MFRC522DriverSPI driver{ss_pin}; // Create SPI driver
// MFRC522DriverI2C driver{};     // Create I2C driver
MFRC522 mfrc522{driver}; // Create MFRC522 instance

// MQTT Setup
const char *ssid = "IT_guys_11";
const char *password = "iotempire";
const char *mqtt_server = "192.168.14.1";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastRead = 0;

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
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  mfrc522.PCD_Init(); // Init MFRC522 board.
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

  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  char uidStr[32] = {0}; // Puffer für UID als String

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    char hexByte[4];
    snprintf(hexByte, sizeof(hexByte), "%02X", mfrc522.uid.uidByte[i]);
    strncat(uidStr, hexByte, sizeof(uidStr) - strlen(uidStr) - 1);
  }
  client.publish("rfid-sensor/uid", uidStr);

  lastRead = millis();
}