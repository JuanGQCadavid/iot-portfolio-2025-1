#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "IT_guys_11";
const char* password = "iotempire";
const char* mqtt_server = "192.168.14.1";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
#define RELEPIN	D2

char msg[MSG_BUFFER_SIZE];

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println("--");

  byte *p = (byte *)malloc(length);
  memcpy(p, payload, length);
  p[length] = '\0';

  Serial.print("Message: ");
  Serial.print((char *)p);
  Serial.println("--");

  if (strcmp((char *)p, "on") == 0)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    client.publish("status/ac", "I'm ON :D");
    digitalWrite(RELEPIN, HIGH);
  }

  if (strcmp((char *)p, "off") == 0)
  {
    digitalWrite(LED_BUILTIN, LOW);
    client.publish("status/ac", "I'm OFF :D");
    digitalWrite(RELEPIN, LOW);
  }
  free(p);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("status/ac", "AC node connected");
      client.subscribe("switch/r1/set");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(RELEPIN, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}