#include <Arduino.h>
#include <FastLED.h>
#include <MoToTimer.h>

#define ray1pin 2
#define ray2pin 1
#define ray3pin 0
#define ray4pin 3
#define ray5pin 4
#define ray6pin 5
#define ray7pin 6
#define ray8pin 7
#define ray9pin 8
#define ray10pin 9
#define ray11pin 10
#define ray12pin 11
#define ray13pin 12
#define ray14pin 13

#define ray1Leds 8
#define ray2Leds 20
#define ray3Leds 20
#define ray4Leds 20
#define ray5Leds 20
#define ray6Leds 20
#define ray7Leds 20
#define ray8Leds 20
#define ray9Leds 20
#define ray10Leds 20
#define ray11Leds 20
#define ray12Leds 20
#define ray13Leds 20
#define ray14Leds 20

CRGB ray1[ray1Leds];
CRGB ray2[ray2Leds];
CRGB ray3[ray3Leds];
CRGB ray4[ray4Leds];
CRGB ray5[ray5Leds];
CRGB ray6[ray6Leds];
CRGB ray7[ray7Leds];
CRGB ray8[ray8Leds];
CRGB ray9[ray9Leds];
CRGB ray10[ray10Leds];
CRGB ray11[ray11Leds];
CRGB ray12[ray12Leds];
CRGB ray13[ray13Leds];
CRGB ray14[ray14Leds];

void setup() {
  pinMode(13, OUTPUT);

  delay(3000);

  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
  FastLED.addLeds<NEOPIXEL,ray1pin>(ray1, ray1Leds);
  FastLED.addLeds<NEOPIXEL,ray2pin>(ray2, ray2Leds);
  FastLED.addLeds<NEOPIXEL,ray3pin>(ray3, ray3Leds);
  FastLED.addLeds<NEOPIXEL,ray4pin>(ray4, ray4Leds);
  FastLED.addLeds<NEOPIXEL,ray5pin>(ray5, ray5Leds);
  FastLED.addLeds<NEOPIXEL,ray6pin>(ray6, ray6Leds);
  FastLED.addLeds<NEOPIXEL,ray7pin>(ray7, ray7Leds);
  FastLED.addLeds<NEOPIXEL,ray8pin>(ray8, ray8Leds);
  FastLED.addLeds<NEOPIXEL,ray9pin>(ray9, ray9Leds);
  FastLED.addLeds<NEOPIXEL,ray10pin>(ray10, ray10Leds);
  FastLED.addLeds<NEOPIXEL,ray11pin>(ray11, ray11Leds);
  FastLED.addLeds<NEOPIXEL,ray12pin>(ray12, ray12Leds);
  FastLED.addLeds<NEOPIXEL,ray14pin>(ray13, ray13Leds);
  FastLED.addLeds<NEOPIXEL,ray14pin>(ray14, ray14Leds);
  
  
  FastLED.clear();
  FastLED.show();
  
}

void loop() 
{
  for(int i = 0; i<ray1Leds;i++)
  {
    digitalWrite(13,HIGH);
    ray1[i] = CRGB::Blue;
    if(i==ray1Leds){i= 0;  digitalWrite(13,LOW); FastLED.clear();FastLED.show();}
    FastLED.show();
    delay(500);
  }
}