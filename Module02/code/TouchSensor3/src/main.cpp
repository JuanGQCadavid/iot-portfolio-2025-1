/*

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 touchSensor = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
*/
// void loop() {
//   // put your main code here, to run repeatedly:
// }

// void setup() {
//   Serial.begin(9600);

//   while (!Serial) { // needed to keep leonardo/micro from starting too fast!
//     delay(10);
//   }

//   Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

//   // Default address is 0x5A, if tied to 3.3V its 0x5B
//   // If tied to SDA its 0x5C and if SCL then 0x5D
//   if (!cap.begin(0x5A)) {
//     Serial.println("MPR121 not found, check wiring?");
//     while (1);
//   }
//   Serial.println("MPR121 found!");
// }

// void loop() {
//   // Get the currently touched pads
//   currtouched = cap.touched();

//   for (uint8_t i=0; i<12; i++) {
//     // it if is touched and wasnt touched before, alert!
//     if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
//       Serial.print(i); Serial.println(" touched");
//     }
//     // if it was touched and now isnt, alert!
//     if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
//       Serial.print(i); Serial.println(" released");
//     }
//   }

//   // reset our state
//   lasttouched = currtouched;

//   // comment out this line for detailed data from the sensor!
//   return;

//   // debugging info, what
//   Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
//   Serial.print("Filt: ");
//   for (uint8_t i=0; i<12; i++) {
//     Serial.print(cap.filteredData(i)); Serial.print("\t");
//   }
//   Serial.println();
//   Serial.print("Base: ");
//   for (uint8_t i=0; i<12; i++) {
//     Serial.print(cap.baselineData(i)); Serial.print("\t");
//   }
//   Serial.println();

//   // put a delay so it isn't overwhelming
//   delay(100);
// }
/*
void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  // Initialize I²C communication
  Wire.begin(A0, D0); // SDA = D2, SCL = D1

  // Initialize the MPR121 sensor
  if (!touchSensor.begin(0x5A))
  { // Default I²C address
    Serial.println("MPR121 not found, check wiring!");
    while (1)
      ;
  }
  Serial.println("MPR121 initialized!");
}

void loop()
{
  uint16_t touchData = touchSensor.touched(); // Read touch inputs

  for (uint8_t i = 0; i < 12; i++)
  { // MPR121 has 12 touch inputs
    if (touchData & (1 << i))
    {
      Serial.print("Touch detected on electrode E");
      Serial.println(i);
    }
  }
  delay(100);
}

*/

#include <Wire.h>
#include "Adafruit_MPR121.h"

#define SDA_PIN D2 // GPIO4
#define SCL_PIN D1 // GPIO5

Adafruit_MPR121 cap = Adafruit_MPR121(); // Initialize the sensor

void setup()
{
  Serial.begin(9600);

  // Initialize I2C on specific pins
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!cap.begin(0x5A))
  { // Check if the sensor is connected (default address is 0x5A)
    Serial.println("Error! MPR121 sensor not found. Check the wiring!");
    while (1)
      ;
  }

  Serial.println("MPR121 sensor is ready!");
}

void loop()
{
  uint16_t touchState = cap.touched(); // Get the current touch state

  for (int i = 0; i < 12; i++)
  {
    if (touchState & (1 << i))
    { // If a pin is touched
      Serial.print("Pin ");
      Serial.print(i);
      Serial.println(" touched");
    }
  }

  delay(200); // Short delay for stability
}