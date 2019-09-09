#include <Arduino.h>
#include "FastLED.h"
#include <main.h>

#define NUM_LEDS 8
CRGB leds[NUM_LEDS];
byte distributionLeds = 4;
int indexSound = -1;
int pinSound = A3;
int pinButton = PB2;
volatile int mode = 0;
volatile boolean flagLantern = false;

void setup() {
  FastLED.addLeds<NEOPIXEL,PB0>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  attachInterrupt(digitalPinToInterrupt(pinButton),status,CHANGE);
}

void status(){
  mode++;
  flagLantern=true;
}

void loop() {
  if(mode > 2){
    mode = 0;
  }
  switch (mode)
  {
    case 0:
      soundMode();
      break;
    case 1:
      colorizeMode();
      break;
    case 2: 
      if(flagLantern){
        lanternMode();
        flagLantern=false;
      }
      break;
    default:
      soundMode();
      break;
  }
}

void colorizeMode() {
  for (int i = 0; i < NUM_LEDS; i++)
  {
    int rn = random(0,9); 
    switch (rn)
    {
    case 0:
        leds[i] = CRGB::Orange;
      break;
    case 1:
        leds[i] = CRGB::Red;
      break;
    case 2:
        leds[i] = CRGB::Yellow;
      break;
    case 3:
        leds[i] = CRGB::ForestGreen;
      break;
    case 4:
        leds[i] = CRGB::AliceBlue;
      break;
    case 5:
        leds[i] = CRGB::Violet;
      break;
    case 6:
        leds[i] = CRGB::Cyan;
      break;
    case 7:
        leds[i] = CRGB::Blue;
      break;
    case 8:
        leds[i] = CRGB::Green;
      break; 
    default:
        leds[i] = CRGB::Black;
      break;
    }
  }
  FastLED.show();
  delay(500);
}

void lanternMode() {
  turnOff();
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::White;
  }
  FastLED.show();
  delay(100);
}

void soundMode() {
  int sound = (int)analogRead(pinSound);
  int index = 0;
  if(sound > 650) {
    index = 4;
  } else if (sound > 600){
    index = 3;
  } else if (sound > 475){
    index = 2;
  } else if (sound > 260){
    index = 1;
  } else {
    index = 0;
  }
  if (indexSound != index){
    showSound(index);
  }
  indexSound = index;
}

void showSound(int c) {
  turnOff();
  for (byte i = distributionLeds-c; i < distributionLeds; i++)
  {
    byte rn = random(0,9);
    switch (rn)
    {
    case 0:
        leds[i] = CRGB::Orange;
        leds[NUM_LEDS-1-i] = CRGB::Orange;
      break;
    case 1:
        leds[NUM_LEDS-1-i] = CRGB::Red;
        leds[i] = CRGB::Red;
      break;
    case 2:
        leds[NUM_LEDS-1-i] = CRGB::Yellow;
        leds[i] = CRGB::Yellow;
      break;
    case 3:
        leds[NUM_LEDS-1-i] = CRGB::ForestGreen;
        leds[i] = CRGB::ForestGreen;
      break;
    case 4:
        leds[NUM_LEDS-1-i] = CRGB::AliceBlue;
        leds[i] = CRGB::AliceBlue;
      break;
    case 5:
        leds[NUM_LEDS-1-i] = CRGB::Violet;
        leds[i] = CRGB::Violet;
      break;
    case 6:
        leds[NUM_LEDS-1-i] = CRGB::Cyan;
        leds[i] = CRGB::Cyan;
      break;
    case 7:
        leds[NUM_LEDS-1-i] = CRGB::Blue;
        leds[i] = CRGB::Blue;
      break;
    case 8:
        leds[NUM_LEDS-1-i] = CRGB::Green;
        leds[i] = CRGB::Green;
      break; 
    default:
        leds[NUM_LEDS-1-i] = CRGB::Black;
        leds[i] = CRGB::Black;
      break;
    }
  }  
  FastLED.show();
  delay(100);
}

void turnOff() {
  for (byte i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(1);   
}