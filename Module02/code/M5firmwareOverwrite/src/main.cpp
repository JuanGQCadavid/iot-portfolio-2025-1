/*
#include <M5StickC.h>

#define SIGNAL_PIN 26 // Pin to send signal to Wemos D1 Mini

void setup()
{
  M5.begin();
  pinMode(SIGNAL_PIN, OUTPUT);
  digitalWrite(SIGNAL_PIN, LOW); // Start LOW
}

void loop()
{
  M5.update(); // Update button state

  if (M5.BtnA.wasPressed())
  {
    Serial.println("Button A Pressed!");
    digitalWrite(SIGNAL_PIN, HIGH); // Send HIGH signal to Wemos
    delay(200);                     // Simple debounce
    digitalWrite(SIGNAL_PIN, LOW);  // Reset signal
  }
}
*/

#include <M5StickC.h>

#define SIGNAL_PIN 26

void setup()
{
  M5.begin();
  Serial.begin(115200);
  pinMode(SIGNAL_PIN, OUTPUT);
  digitalWrite(SIGNAL_PIN, LOW); // Default to LOW
}

void loop()
{
  Serial.println("Setting GPIO 26 HIGH");
  digitalWrite(SIGNAL_PIN, HIGH);
  delay(1000);

  Serial.println("Setting GPIO 26 LOW");
  digitalWrite(SIGNAL_PIN, LOW);
  delay(1000);
}