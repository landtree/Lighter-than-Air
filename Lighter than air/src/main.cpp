#include <Arduino.h>
#include <FastLED.h>
#include <MoToTimer.h>

MoToTimer SwitchEffect;
MoToTimer splashUpdate;

int effectTime = 1000;
int splashTime = 30;
bool splashDir = true;

byte pos = 1;
int hue = 5;

#define ray1pin 0
#define ray2pin 1
#define ray3pin 2
#define ray4pin 3
#define ray5pin 9
#define ray6pin 10
#define ray7pin 11
#define ray8pin 12
#define ray9pin 13
#define ray10pin 4
#define ray11pin 5


#define ray1Leds 22
#define ray2Leds 22
#define ray3Leds 31
#define ray4Leds 31
#define ray5Leds 40
#define ray6Leds 40
#define ray7Leds 15
#define ray8Leds 15
#define ray9Leds 15
#define ray10Leds 15
#define ray11Leds 23


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

#define ray5aLeds 20
#define ray5bLeds 20
CRGB* ray5a = ray5;
CRGB* ray5b = ray5 + ray5aLeds;

#define ray7aLeds 6
#define ray7bLeds 9
CRGB* ray7a = ray7;
CRGB* ray7b = ray7 + ray7aLeds;

#define ray8aLeds 6
#define ray8bLeds 9
CRGB* ray8a = ray8;
CRGB* ray8b = ray8 + ray8aLeds;

int posRay3 = ray3Leds - 1;
int posRay5a = 0;
int posRay5b = 0;
int posRay7a = 0;
int posRay7b = 0;
int posRay5 = 0;
int posRay7 = 0;
int posRay8 = 0;
int posRay8a = 0;
int posRay8b = 0;
bool ray3_finished = false;
bool ray5_finished = false;
bool ray7_finished = false;
bool ray8_finished = false;

bool fadeStarted = false;
int fadeCounter = 0;

void setup() {
  pinMode(13, OUTPUT);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
  delay(1000);

  
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
  
  Serial.begin(9600);
  FastLED.clear();
  FastLED.show();
  SwitchEffect.setTime(effectTime);
  splashUpdate.setTime(splashTime);
}


void splash() {
  // reset all LEDS to off
  fill_solid( ray3, ray3Leds, CRGB::Black);
  fill_solid( ray5a, ray5aLeds, CRGB::Black);
  fill_solid( ray5b, ray5bLeds, CRGB::Black);
  fill_solid( ray7a, ray7aLeds, CRGB::Black);
  fill_solid( ray7b, ray7bLeds, CRGB::Black);
  fill_solid( ray8a, ray8aLeds, CRGB::Black);
  fill_solid( ray8b, ray8bLeds, CRGB::Black);
  
  // Splash animation for ray3
  if (!ray3_finished) {
    if (posRay3 >= 0) {
      ray3[posRay3] = CRGB::Aqua;
      if (posRay3 + 1 < ray3Leds) 
        ray3[posRay3 + 1] = CRGB::Aqua;
        ray3[posRay3 + 1] = ray3[posRay3 + 1].nscale8(128);
      if (posRay3 + 2 < ray3Leds) 
        ray3[posRay3 + 2] = CRGB::Aqua;
        ray3[posRay3 + 2] = ray3[posRay3 + 2].nscale8(128);

      posRay3--;
    } else {
      posRay3 = ray3Leds - 1;
      ray3_finished = true;
    }
  } 
  
  // Splash animation for ray5
  else if (!ray5_finished) {
    if (posRay5a < ray5aLeds) {
      ray5a[posRay5a] = CRGB::Aqua;
      if (posRay5a + 1 < ray5aLeds) 
        ray5a[posRay5a + 1] = CRGB::Aqua.nscale8(128);
      if (posRay5a + 2 < ray5aLeds) 
        ray5a[posRay5a + 2] = CRGB::Aqua.nscale8(128);
        
      posRay5a++;
    } 
    if (posRay5b < ray5bLeds) {
      ray5b[posRay5b] = CRGB::Aqua;
      if (posRay5b + 1 < ray5bLeds) 
        ray5b[posRay5b + 1] = CRGB::Aqua.nscale8(128);
      if (posRay5b + 2 < ray5bLeds) 
        ray5b[posRay5b + 2] = CRGB::Aqua.nscale8(128);
        
      posRay5b++;
    } 
    if (posRay5a >= ray5aLeds && posRay5b >= ray5bLeds) {
      posRay5a = 0;
      posRay5b = 0;
      ray5_finished = true;
    }
  }
  
  // Splash animation for ray7
  else if (!ray7_finished) {
    if (posRay7a < ray7aLeds) {
      ray7a[posRay7a] = CRGB::Aqua;
      if (posRay7a + 1 < ray7aLeds) 
        ray7a[posRay7a + 1] = CRGB::Aqua.nscale8(128);
      if (posRay7a + 2 < ray7aLeds) 
        ray7a[posRay7a + 2] = CRGB::Aqua.nscale8(128);
        
      posRay7a++;
    } 
    if (posRay7b < ray7bLeds) {
      ray7b[posRay7b] = CRGB::Aqua;
      if (posRay7b + 1 < ray7bLeds) 
        ray7b[posRay7b + 1] = CRGB::Aqua.nscale8(128);
      if (posRay7b + 2 < ray7bLeds) 
        ray7b[posRay7b + 2] = CRGB::Aqua.nscale8(128);
        
      posRay7b++;
    } 
    if (posRay7a >= ray7aLeds && posRay7b >= ray7bLeds) {
      posRay7a = 0;
      posRay7b = 0;
      ray7_finished = true;
    }
  }

  // Splash animation for ray8
  else if (!ray8_finished) {
    if (posRay8a < ray8aLeds) {
      ray8a[posRay8a] = CRGB::Aqua;
      if (posRay8a + 1 < ray8aLeds) 
        ray8a[posRay8a + 1] = CRGB::Aqua.nscale8(128);
      if (posRay8a + 2 < ray8aLeds) 
        ray8a[posRay8a + 2] = CRGB::Aqua.nscale8(128);
        
      posRay8a++;
    } 
    if (posRay8b < ray8bLeds) {
      ray8b[posRay8b] = CRGB::Aqua;
      if (posRay8b + 1 < ray8bLeds) 
        ray8b[posRay8b + 1] = CRGB::Aqua.nscale8(128);
      if (posRay8b + 2 < ray8bLeds) 
        ray8b[posRay8b + 2] = CRGB::Aqua.nscale8(128);
        
      posRay8b++;
    } 
    if (posRay8a >= ray8aLeds && posRay8b >= ray8bLeds) {
      posRay8a = 0;
      posRay8b = 0;
      ray8_finished = true;
    }
  } else {
    ray3_finished = false;
    ray5_finished = false;
    ray7_finished = false;
    ray8_finished = false;
  }

  FastLED.show();
}



void loop() {

if(!SwitchEffect.running())
{
  Serial.println(pos);
  //pos++; not currently in use.
  SwitchEffect.restart();  
}
switch (pos)
{
case 1:
  if(!splashUpdate.running())
    {
      splash();
    }


  break;
case 2:
 fill_rainbow(ray1,ray1Leds,40,hue);
 fill_rainbow(ray2,ray2Leds,40,hue);
 fill_rainbow(ray3,ray3Leds,40,hue);
 fill_rainbow(ray4,ray4Leds,40,hue);
 fill_rainbow(ray5,ray5Leds,40,hue);
 fill_rainbow(ray6,ray6Leds,40,hue);
 fill_rainbow(ray7,ray7Leds,40,hue);
 fill_rainbow(ray8,ray8Leds,40,hue);
 fill_rainbow(ray9,ray8Leds,40,hue);
 fill_rainbow(ray10,ray10Leds,40,hue);
 fill_rainbow(ray11,ray11Leds,40,hue);
 FastLED.show();
EVERY_N_MILLISECONDS(50){hue++;};
 break;
case 3:

  break;
case 4:

  break;
case 5:

  break;
case 6:

  break;
case 7:

  break;
case 8:

  break;
case 9:

  break;
case 10:

  break;
case 11:
  pos = 0;
  break;

}


}