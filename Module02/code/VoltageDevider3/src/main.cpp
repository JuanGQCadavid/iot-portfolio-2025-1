#include <Arduino.h>

#define Analog_in A0

void setup()
{
  pinMode(Analog_in, INPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Metered Voltage: ");
  Serial.println((3.3 / 1023.0) * analogRead(Analog_in));
  delay(1000);
}
