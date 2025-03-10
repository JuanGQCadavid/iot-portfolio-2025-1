/*
#include "FastLED.h"

#define NUM_LEDS 10
#define DATA_PIN D0

CRGB leds[NUM_LEDS];

int ledPos = 0;

void setup()
{
  Serial.begin(9600);
  delay(3000);
  random16_add_entropy(analogRead(0));
  pinMode(D8, INPUT);

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

void loop()
{
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  EVERY_N_MILLIS(500)
  {
    ledPos = ledPos + 1;
  }
  setLed(ledPos, CRGB::Blue);
  FastLED.show();
  ;

  if (ledPos >= NUM_LEDS)
  {
    ledPos = 0;
  }
  Serial.println(digitalRead(D8));
}
*/
// #include <Arduino.h>
// #define BUTTON_1 D8 // Pin connected to M5StickC GPIO 26
// #define BUTTON_2 D5

// void setup()
// {
//   Serial.begin(9600);
//   pinMode(BUTTON_1, INPUT);
//   pinMode(BUTTON_2, INPUT);
// }

// void loop()
// {
//   if (digitalRead(BUTTON_1) == HIGH)
//   {
//     Serial.println("Button 1!");
//   }
//   if (digitalRead(BUTTON_2) == HIGH)
//   {
//     Serial.println("Button 2!");
//   }
//   delay(100);
// }

#include <Arduino.h>
#include "FastLED.h"

#define NUM_LEDS 10
#define DATA_PIN D1
#define MOVE_LEFT_PIN D8
#define MOVE_RIGHT_PIN D5

struct Bomb
{
  int pos;
  unsigned long startTime;
  int duration;
};

CRGB leds[NUM_LEDS];
Bomb bomb = Bomb();
int score = 0;
int playerPos = 0;
int wallPos = 0;

int getDistance(int p1, int p2)
{
  int distance = abs(p2 - p1);
  if (distance < NUM_LEDS / 2)
  {
    return distance;
  }
  else
  {
    return NUM_LEDS - distance;
  }
}

void moveWall()
{
  do
  {
    wallPos = random16(NUM_LEDS);
  } while (getDistance(wallPos, bomb.pos) < 2 || getDistance(wallPos, playerPos) < 2);
}

void moveBomb()
{
  do
  {
    bomb.pos = random16(NUM_LEDS);
  } while (bomb.pos == playerPos);

  bomb.startTime = millis();
  bomb.duration = max(1500, 5000 - (score * 100));
}

void startGame()
{
  bomb = Bomb();
  score = 0;
  playerPos = 0;

  moveBomb();
  moveWall();
}

void movePlayer()
{
  if (digitalRead(MOVE_LEFT_PIN) == LOW)
  {
    playerPos = (playerPos - 1 + NUM_LEDS) % NUM_LEDS;
  }
  else if (digitalRead(MOVE_RIGHT_PIN) == LOW)
  {
    playerPos = (playerPos + 1) % NUM_LEDS;
  }
}

CRGB getBombColor(int timeLeft)
{
  int brightness = map(timeLeft, bomb.duration, 0, 0, 255);
  if (timeLeft < 1000)
  {
    brightness = beatsin8(240, 0, 255);
  }

  return CRGB(brightness, brightness, 0);
}

void setLed(int index, CRGB color)
{
  if (index >= 0 && index < NUM_LEDS)
  {
    leds[index] = color;
  }
}

void gameOver(int pos)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    setLed(pos - i, CRGB::Red);
    setLed(pos + i, CRGB::Red);
    FastLED.show();
    delay(30);
  }
  delay(500);

  for (int i = 255; i >= 0; i--)
  {
    fill_solid(leds, NUM_LEDS, CRGB(i, 0, 0));
    FastLED.show();
    delay(4);
  }

  startGame();
}

void setup()
{
  delay(3000);
  random16_add_entropy(analogRead(0));

  pinMode(MOVE_LEFT_PIN, INPUT_PULLUP);
  pinMode(MOVE_RIGHT_PIN, INPUT_PULLUP);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(160);
  startGame();
}

void loop()
{
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  EVERY_N_MILLIS(100)
  {
    movePlayer();

    if (playerPos == bomb.pos)
    {
      score++;
      moveBomb();
      moveWall();
    }
  }

  setLed(playerPos, CRGB::Blue);
  setLed(wallPos, CRGB::Red);

  int bombTimeLeft = bomb.duration - (millis() - bomb.startTime);
  setLed(bomb.pos, getBombColor(bombTimeLeft));

  if (bombTimeLeft <= 0)
  {
    gameOver(bomb.pos);
  }
  else if (playerPos == wallPos)
  {
    gameOver(wallPos);
  }

  FastLED.show();
}