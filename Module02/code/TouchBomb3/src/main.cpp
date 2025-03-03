#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "FastLED.h"

#define NUM_LEDS 10
#define DATA_PIN D1
#define SDA_PIN D3
#define SCL_PIN D4

CRGB leds[NUM_LEDS];
Adafruit_MPR121 cap = Adafruit_MPR121(); // Initialize the sensor
int ledPos = 0;

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

  delay(3000);
  pinMode(DATA_PIN, OUTPUT);
  // pinMode(SDA_PIN, INPUT);
  // pinMode(SCL_PIN, OUTPUT);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(160);
}

void setLed(int index, CRGB color)
{
  if (index >= 0 && index < NUM_LEDS)
  {
    leds[index] = color;
  }
}

int martinPointer = 0;
int martinButton = 2;

int juanPointer = 9;
int juanButton = 6;

bool previousTouchStateMartin = false;
bool previousTouchStateJuan = false;

bool touchStateMartin = false;
bool touchStateJuan = false;

void loop()
{
  uint16_t touchState = cap.touched(); // Get the current touch state

  bool currentTouchStateMartin = touchState & (1 << martinButton);
  bool currentTouchStateJuan = touchState & (1 << juanButton);

  if (previousTouchStateMartin == false && currentTouchStateMartin == true)
  {
    touchStateMartin = true;
  }
  if (previousTouchStateJuan == false && currentTouchStateJuan == true)
  {
    touchStateJuan = true;
  }

  if (juanPointer >= (martinPointer + 1))
  {
    if (touchState & (1 << martinButton))
    { // If a pin is touched
      if (previousTouchStateMartin == false)
      {
        setLed(martinPointer, CRGB::Green);
        martinPointer++;
        previousTouchStateMartin = true;
      }
    }
    else
    {
      previousTouchStateMartin = false;
    }

    if (touchState & (1 << juanButton))
    { // If a pin is touched
      if (previousTouchStateJuan == false)
      {
        setLed(juanPointer, CRGB::Blue);
        juanPointer--;
        previousTouchStateJuan = true;
      }
    }
    else
    {
      previousTouchStateJuan = false;
    }
    FastLED.show();
  }
  else if (touchStateMartin && touchStateJuan)
  {
    return;
  }
  else if (touchStateMartin != touchStateJuan)
  {
    if (touchStateMartin)
    {
      setLed(martinPointer, CRGB::Green);
      martinPointer++;
    }
    if (touchStateJuan)
    {
      setLed(juanPointer, CRGB::Blue);
      juanPointer--;
    }
    FastLED.show();
  }

  delay(100);
}

// void loop()
// {
//   fill_solid(leds, NUM_LEDS, CRGB::Black);
//   EVERY_N_MILLIS(500)
//   {
//     ledPos = ledPos + 1;
//   }
//   setLed(ledPos, CRGB::Blue);
//   FastLED.show();
//   ;

//   if (ledPos >= NUM_LEDS)
//   {
//     ledPos = 0;
//   }
//   Serial.println(digitalRead(D8));
// }
/*
void loop()
{

  if (touchState & (1 << martinButton))
  { // If a pin is touched
    if (previousTouchStateMartin == false)
    {
      setLed(martinPointer, CRGB::Green);
      martinPointer++;
      previousTouchStateMartin = true;
    }
  }
  else
  {
    previousTouchStateMartin = false;
  }

  if (touchState & (1 << juanButton))
  { // If a pin is touched
    if (previousTouchStateJuan == false)
    {
      setLed(juanPointer, CRGB::Blue);
      juanPointer--;
      previousTouchStateJuan = true;
    }
  }
  else
  {
    previousTouchStateJuan = false;
  }
  FastLED.show();
}
  */

/*
void loop()
{
  uint16_t touchState = cap.touched(); // Get the current touch state

  touchStateMartin = false;
  touchStateJuan = false;
  bool currentTouchStateMartin = touchState & (1 << martinButton);
  bool currentTouchStateJuan = touchState & (1 << juanButton);

  if (previousTouchStateMartin == false && currentTouchStateMartin == true)
  {
    touchStateMartin = true;
    previousTouchStateMartin = true;
  }
  if (previousTouchStateJuan == false && currentTouchStateJuan == true)
  {
    touchStateJuan = true;
    previousTouchStateJuan = true;
  }

  if (previousTouchStateMartin == true && currentTouchStateMartin == false)
  {
    touchStateMartin = false;
    previousTouchStateMartin = false;
  }
  if (previousTouchStateJuan == true && currentTouchStateJuan == false)
  {
    touchStateJuan = false;
    previousTouchStateJuan = false;
  }

  if (juanPointer >= (martinPointer + 1))
  {
    if (touchStateMartin)
    {
      setLed(martinPointer, CRGB::Green);
      martinPointer++;
    }
    if (touchStateJuan)
    {
      setLed(juanPointer, CRGB::Blue);
      juanPointer++;
    }
  }
  else if (touchStateMartin && touchStateJuan)
  {
    return;
  }
  else if (touchStateMartin != touchStateJuan)
  {
    if (touchStateMartin)
    {
      setLed(martinPointer, CRGB::Green);
      martinPointer++;
      juanPointer++;
    }
    if (touchStateJuan)
    {
      setLed(juanPointer, CRGB::Blue);
      juanPointer--;
      martinPointer--;
    }
  }
  FastLED.show();

  delay(100);
}
*/