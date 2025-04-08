#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define WIRE Wire

const char* ssid = "IT_guys_11";
const char* password = "iotempire";
const char* mqtt_server = "192.168.14.1";


WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &WIRE);


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

void printOnLedEmpty(){
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println();
  display.println(String("      "));
  display.println("       :eyes:");
  display.println("       ");
  display.setCursor(0,0);
  display.display(); // actually display all of the above
}

void printOnLed(char* message){
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println();
  display.println(String("      ") + message);
  display.println("       Welcome");
  display.println("       back!");
  display.setCursor(0,0);
  display.display(); // actually display all of the above
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

  // HERE display the thing

  // unsigned long now = millis();
  // if ((millis() - now ) <= 2000) {
  //   // lastMsg = now;
  //   printOnLed((char *)p);
  // }

  printOnLed((char *)p);
  delay(5000);
  Serial.println("Lets clean the screem");
  printOnLedEmpty();
  free(p);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("status/display", "node connected");
      client.subscribe("rfid-sensor/uid");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  Serial.begin(9600);

  Serial.println("OLED FeatherWing test");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  Serial.println("IO test");

  // display.setTextSize(1);
  // display.setTextColor(SSD1306_WHITE);
  // display.setCursor(0,0);
  // display.print("Before");
  // display.print("Martiinnnn");
  // display.println("IP: 10.0.1.23");
  // display.println("Sending val #0");
  // display.setCursor(0,0);
  // display.display(); // actually display all of the above

  printOnLedEmpty();
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}