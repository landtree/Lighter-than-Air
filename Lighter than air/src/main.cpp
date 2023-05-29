#include <Arduino.h>
#include <FastLED.h>
#include <MoToTimer.h>

MoToTimer SwitchEffect;
MoToTimer splashUpdate;
MoToTimer rippleUpdate;

int effectTime = 10000;
int splashTime = 30;
int rippleTime = 80;
bool splashDir = true;
bool newNum = false;
bool dir = true;
int hueShift = 0;

byte bright = 1;
byte pos = 1;
int hue = 5;
byte fadeVal = 11;

// define the colors
CRGB red = CRGB::Red;
CRGB purple = CRGB::Purple;

MoToTimer chaseTimer;
MoToTimer fadeTimer;
int chaseTime = 50; // time in milliseconds, adjust for desired speed
int fadeTime = 20; // time in milliseconds, adjust for desired fade speed
int currentSection = 0; // keep track of the current section
int currentLed = 0; // keep track of the current LED within the section
int prevSection = 0; // keep track of the previous section
int prevLed = 0; // keep track of the previous LED within the section
bool forward = true; // whether we're moving forward or backward
int fadeSection = -1; // keeps track of the section currently fading out, -1 means no section is fading
int fadeLed = 0; // keeps track of the LED currently fading out


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

#define ray1aLeds 4
#define ray1bLeds 4
#define ray1cLeds 5
#define ray1dLeds 4
#define ray1eLeds 5

#define ray2aLeds 4
#define ray2bLeds 4
#define ray2cLeds 5
#define ray2dLeds 4
#define ray2eLeds 5


// Split the LED array into logical strips
CRGB* ray1a = &ray1[0];                           // Pointer to strip A
CRGB* ray1b = &ray1[ray1aLeds];                    // Pointer to strip B
CRGB* ray1c = &ray1[ray1aLeds + ray1bLeds];        // Pointer to strip C
CRGB* ray1d = &ray1[ray1aLeds + ray1bLeds + ray1cLeds];  // Pointer to strip D
CRGB* ray1e = &ray1[ray1aLeds + ray1bLeds + ray1cLeds + ray1dLeds];  // Pointer to strip E

// Split the LED array into logical strips
CRGB* ray2a = &ray2[0];                           // Pointer to strip A
CRGB* ray2b = &ray2[ray2aLeds];                    // Pointer to strip B
CRGB* ray2c = &ray2[ray2aLeds + ray2bLeds];        // Pointer to strip C
CRGB* ray2d = &ray2[ray2aLeds + ray2bLeds + ray2cLeds];  // Pointer to strip D
CRGB* ray2e = &ray2[ray2aLeds + ray2bLeds + ray2cLeds + ray2dLeds];  // Pointer to strip E

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

#define ray6aLeds 20
#define ray6bLeds 20
CRGB* ray6a = ray6;
CRGB* ray6b = ray6 + ray6aLeds;

#define ray10aLeds 6
#define ray10bLeds 9
CRGB* ray10a = ray10;
CRGB* ray10b = ray10 + ray10aLeds;

#define ray9aLeds 6
#define ray9bLeds 9
CRGB* ray9a = ray9;
CRGB* ray9b = ray9 + ray9aLeds;
  

// Positions
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
int posRay4 = ray4Leds - 1;
int posRay6a = 0;
int posRay6b = 0;
int posRay10a = 0;
int posRay10b = 0;
int posRay9a = 0;
int posRay9b = 0;

// Finished flags
bool ray4_finished = false;
bool ray6_finished = false;
bool ray10_finished = false;
bool ray9_finished = false;
bool ray3_finished = false;
bool ray5_finished = false;
bool ray7_finished = false;
bool ray8_finished = false;

bool fadeStarted = false;
int fadeCounter = 0;


//twinkle
// Create an array for the colors
// Create multiple groups of colors
CRGB colorGroup1[] = {CRGB::White, CRGB::Aqua, CRGB::Blue, CRGB::Green};
CRGB colorGroup2[] = {CRGB::Red, CRGB::Orange, CRGB::Yellow, CRGB::Pink};
CRGB colorGroup3[] = {CRGB::Purple, CRGB::Violet, CRGB::Indigo, CRGB::Magenta};

CRGB* colorGroups[] = {colorGroup1, colorGroup2, colorGroup3};
int colorGroupSizes[] = {sizeof(colorGroup1) / sizeof(colorGroup1[0]), 
                         sizeof(colorGroup2) / sizeof(colorGroup2[0]),
                         sizeof(colorGroup3) / sizeof(colorGroup3[0])};


void setup() {
  pinMode(13, OUTPUT);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2300);
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
  rippleUpdate.setTime(rippleTime);
  chaseTimer.setTime(chaseTime);
  randomSeed(analogRead(0));
}

void applyRainbow(CRGB* leds, int start, int end) {
  uint8_t time = millis() / 5; // Adjust divisor to control speed
  for (int i = start; i < end; i++) {
    leds[i] = CHSV((i + time) % 256, 255, 255);
  }
}

struct Section {
  CRGB* array;
  int start;
  int end;
};

Section sections[] = {
  { ray1, 0, ray1Leds },
  { ray7a, 0, ray7aLeds },
  { ray7b, 0, ray7bLeds },
  { ray5a, 0, ray5aLeds },
  { ray3, 0, ray3Leds },
  { ray5b, 0, ray5bLeds },
  { ray8b, 0, ray8bLeds },
  { ray8a, 0, ray8aLeds },
  { ray2, 0, ray2Leds },
  { ray9a, 0, ray9aLeds },
  { ray9b, 0, ray9bLeds },
  { ray6a, 0, ray6aLeds },
  { ray4, 0, ray4Leds },
  { ray6b, 0, ray6bLeds },
  { ray10a, 0, ray10aLeds },
  { ray10b, 0, ray10bLeds },
   { ray11, 0, ray11Leds },
};

int numSections = sizeof(sections) / sizeof(sections[0]);

void fadeUpdate(int fadeAmount) {

    for (int i = 0; i < numSections; i++) {
    Section &section = sections[i];
    for (int j = section.start; j < section.end; j++) {
      // Apply a fade to each LED
      section.array[j].fadeToBlackBy(fadeAmount);
    }
  }
  FastLED.show();
}



void rainbowUpdate()
{

  for (int i = 0; i < numSections; i++) {
    Section &section = sections[i];
    applyRainbow(section.array, section.start, section.end);
    fadeUpdate(fadeVal);
  }  
  FastLED.show();
}

void chase()
{
      // Set the current LED to red
    sections[currentSection].array[currentLed] = red;

    // Set the preceding and following LEDs to purple, if they exist
    for (int i = 1; i <= 3; i++) {
      if (currentLed - i >= 0) {
        sections[currentSection].array[currentLed - i] = purple;
        sections[currentSection].array[currentLed - i].fadeToBlackBy(255 * i / 4);
      }
      if (currentLed + i < sections[currentSection].end) {
        sections[currentSection].array[currentLed + i] = purple;
        sections[currentSection].array[currentLed + i].fadeToBlackBy(255 * i / 8);
      }
    }

    // Update the LEDs
    FastLED.show();

    // Move on to the next LED
    if (forward) {
      currentLed++;
      if (currentLed + 3 >= sections[currentSection].end) {
        // We've reached the end of this section, move on to the next one
        fadeSection = currentSection; // start fading out the current section
        fadeLed = 0; // start fading from the first LED
        forward = !forward;
        // Move to the next section
        currentSection = (currentSection + 1) % numSections;
        currentLed = sections[currentSection].end - 1; // Reset for the next direction
      }
    } else {
      currentLed--;
      if (currentLed - 3 < 0) {
        // We've reached the beginning of this section, move on to the next one
        fadeSection = currentSection; // start fading out the current section
        fadeLed = 0; // start fading from the first LED
        forward = !forward;
        // Move to the next section
        currentSection = (currentSection + 1) % numSections;
        currentLed = 0; // Reset for the next direction
      }
    }
    // Reset the timer
    chaseTimer.restart();


}

void randomTwinkle() {
  // Select a random section
  int sectionIndex = random(numSections);
  Section &section = sections[sectionIndex];
  
  // Calculate half of the LEDs in this section
  int halfLeds = section.end / 2;

  // Turn off all LEDs in the section
  for (int i = 0; i < section.end; i++) {
    section.array[i] = CRGB::Black;
  }

  // Select a random color group
  int colorGroupIndex = random(sizeof(colorGroups) / sizeof(colorGroups[0]));
  CRGB* colorGroup = colorGroups[colorGroupIndex];
  int colorGroupSize = colorGroupSizes[colorGroupIndex];

  // Twinkle half of the LEDs in the section
  for (int i = 0; i < halfLeds; i++) {
    // Select a random LED within the section
    int ledIndex = random(section.end);
    
    // Select a random color from the color group
    CRGB color = colorGroup[random(colorGroupSize)];

    // Select a random brightness (from 0 to 255)
    uint8_t brightness = random(256);
    
    // Set the LED to the selected color and brightness
    section.array[ledIndex] = color;
    section.array[ledIndex].nscale8(brightness);
  }
  
  // Update the LEDs
  FastLED.show();
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
  fill_solid( ray4, ray4Leds, CRGB::Black);
  fill_solid( ray6a, ray6aLeds, CRGB::Black);
  fill_solid( ray6b, ray6bLeds, CRGB::Black);
  fill_solid( ray10a, ray10aLeds, CRGB::Black);
  fill_solid( ray10b, ray10bLeds, CRGB::Black);
  fill_solid( ray9a, ray9aLeds, CRGB::Black);
  fill_solid( ray9b, ray9bLeds, CRGB::Black);
  
  // Splash animation for ray3
  if (!ray3_finished) {
    if (posRay3 >= 0) {
      ray3[posRay3] = CRGB::Aqua;
      if (posRay3 + 1 < ray3Leds) 
        ray3[posRay3 + 1] = CRGB(CRGB::Aqua).nscale8(128);
      if (posRay3 + 2 < ray3Leds) 
        ray3[posRay3 + 2] = CRGB(CRGB::Aqua).nscale8(128);
      
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
        ray5a[posRay5a + 1] = CRGB(CRGB::Aqua).nscale8(128);
      if (posRay5a + 2 < ray5aLeds) 
        ray5a[posRay5a + 2] = CRGB(CRGB::Aqua).nscale8(128);
        
      posRay5a++;
    } 
    if (posRay5b < ray5bLeds) {
      ray5b[posRay5b] = CRGB::Aqua;
      if (posRay5b + 1 < ray5bLeds) 
        ray5b[posRay5b + 1] = CRGB(CRGB::Aqua).nscale8(128);
      if (posRay5b + 2 < ray5bLeds) 
        ray5b[posRay5b + 2] = CRGB(CRGB::Aqua).nscale8(128);
        
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
        ray7a[posRay7a + 1] = CRGB(CRGB::Aqua).nscale8(128);
      if (posRay7a + 2 < ray7aLeds) 
        ray7a[posRay7a + 2] = CRGB(CRGB::Aqua).nscale8(128);
        
      posRay7a++;
    } 
    if (posRay7b < ray7bLeds) {
      ray7b[posRay7b] = CRGB::Aqua;
      if (posRay7b + 1 < ray7bLeds) 
        ray7b[posRay7b + 1] = CRGB(CRGB::Aqua).nscale8(128);
      if (posRay7b + 2 < ray7bLeds) 
        ray7b[posRay7b + 2] = CRGB(CRGB::Aqua).nscale8(128);
        
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
        ray8a[posRay8a + 1] = CRGB(CRGB::Aqua).nscale8(128);
      if (posRay8a + 2 < ray8aLeds) 
        ray8a[posRay8a + 2] = CRGB(CRGB::Aqua).nscale8(128);
        
      posRay8a++;
    } 
    if (posRay8b < ray8bLeds) {
      ray8b[posRay8b] = CRGB::Aqua;
      if (posRay8b + 1 < ray8bLeds) 
        ray8b[posRay8b + 1] = CRGB(CRGB::Aqua).nscale8(128);
      if (posRay8b + 2 < ray8bLeds) 
        ray8b[posRay8b + 2] = CRGB(CRGB::Aqua).nscale8(128);
        
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

    // Splash animation for ray4
  if (!ray4_finished) {
    if (posRay4 >= 0 && posRay4 < ray4Leds) {
      ray4[posRay4] = CRGB::Aqua;
      if (posRay4 < ray4Leds - 1) 
        ray4[posRay4 + 1].nscale8(128);
      if (posRay4 < ray4Leds - 2) 
        ray4[posRay4 + 2].nscale8(128);
      posRay4--;
    } else {
      posRay4 = ray4Leds - 1;
      ray4_finished = true;
    }
  }
  // Splash animation for ray6
  else if (!ray6_finished) {
    if (posRay6a < ray6aLeds || posRay6b < ray6bLeds) {
      if (posRay6a < ray6aLeds) {
        ray6a[posRay6a] = CRGB::Aqua;
        if (posRay6a > 0) 
          ray6a[posRay6a - 1].nscale8(128);
        if (posRay6a > 1) 
          ray6a[posRay6a - 2].nscale8(128);
        posRay6a++;
      }
      if (posRay6b < ray6bLeds) {
        ray6b[posRay6b] = CRGB::Aqua;
        if (posRay6b > 0) 
          ray6b[posRay6b - 1].nscale8(128);
        if (posRay6b > 1) 
          ray6b[posRay6b - 2].nscale8(128);
        posRay6b++;
      }
    } else {
      posRay6a = 0;
      posRay6b = 0;
      ray6_finished = true;
    }
  }
  // Splash animation for ray10 and ray9
  else if (!ray10_finished || !ray9_finished) {
    if (posRay10a < ray10aLeds || posRay10b < ray10bLeds || posRay9a < ray9aLeds || posRay9b < ray9bLeds) {
      if (posRay10a < ray10aLeds) {
        ray10a[posRay10a] = CRGB::Aqua;
        if (posRay10a > 0) 
          ray10a[posRay10a - 1].nscale8(128);
        if (posRay10a > 1) 
          ray10a[posRay10a - 2].nscale8(128);
        posRay10a++;
      }
      if (posRay10b < ray10bLeds) {
        ray10b[posRay10b] = CRGB::Aqua;
        if (posRay10b > 0) 
          ray10b[posRay10b - 1].nscale8(128);
        if (posRay10b > 1) 
          ray10b[posRay10b - 2].nscale8(128);
        posRay10b++;
      }
      if (posRay9a < ray9aLeds) {
        ray9a[posRay9a] = CRGB::Aqua;
        if (posRay9a > 0) 
          ray9a[posRay9a - 1].nscale8(128);
        if (posRay9a > 1) 
          ray9a[posRay9a - 2].nscale8(128);
        posRay9a++;
      }
      if (posRay9b < ray9bLeds) {
        ray9b[posRay9b] = CRGB::Aqua;
        if (posRay9b > 0) 
          ray9b[posRay9b - 1].nscale8(128);
        if (posRay9b > 1) 
          ray9b[posRay9b - 2].nscale8(128);
        posRay9b++;
      }
    } else {
      posRay10a = 0;
      posRay10b = 0;
      ray10_finished = true;
      posRay9a = 0;
      posRay9b = 0;
      ray9_finished = true;
    }
  }
  // Reset the variables to start the animation again
  else {
    ray4_finished = false;
    ray6_finished = false;
    ray10_finished = false;
    ray9_finished = false;
  }

  FastLED.show();
}



void loop() {

if(!SwitchEffect.running())
{
  if(!newNum){pos = 2;} 

  if(newNum)
  {
    do
    {
      pos = random(1,9);
      Serial.println(pos);
    } while (pos == 2);
    newNum = false;
  }  
  SwitchEffect.restart();

}


switch (pos)
{
case 1:
  if(!splashUpdate.running())
    {
      splash();
      splashUpdate.restart();
    }
  break;
case 2:
 fadeToBlackBy(ray1,ray1Leds,5);
 fadeToBlackBy(ray2,ray2Leds,5);
 fadeToBlackBy(ray3,ray3Leds,5);
 fadeToBlackBy(ray4,ray4Leds,5);
 fadeToBlackBy(ray5,ray5Leds,5);
 fadeToBlackBy(ray6,ray6Leds,5);
 fadeToBlackBy(ray7,ray7Leds,5);
 fadeToBlackBy(ray8,ray8Leds,5);
 fadeToBlackBy(ray9,ray9Leds,5);
 fadeToBlackBy(ray10,ray10Leds,5);
 fadeToBlackBy(ray11,ray11Leds,5);
 newNum = true;
 FastLED.show();  
 break;

case 3:
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
case 4:
 if(!rippleUpdate.running())
 {
  rainbowUpdate();
  rippleUpdate.restart();
 }
  break;
case 5:
  if(!fadeTimer.running())
  {
    fadeUpdate(5);
    fadeTimer.restart();
  }
  if(!chaseTimer.running())
  {  
    chase();
  }
  break;
case 6:
  if(!fadeTimer.running())
  {
    fadeUpdate(25);
    fadeTimer.restart();
  }
  randomTwinkle();
  break;
case 7:
  fill_gradient(ray3,ray3Leds,CHSV(140,255,255), CHSV(160,255,bright));
  fill_gradient(ray4,ray4Leds,CHSV(140,255,255), CHSV(160,255,bright));
  fill_gradient(ray5a,ray5aLeds,CHSV(160,255,255), CHSV(200,255,bright));
  fill_gradient(ray6a,ray6aLeds,CHSV(160,255,255), CHSV(200,255,bright));
  fill_gradient(ray5b,ray5bLeds,CHSV(160,255,255), CHSV(200,255,bright));
  fill_gradient(ray6b,ray6bLeds,CHSV(160,255,255), CHSV(200,255,bright));

  fill_gradient(ray1a,ray1aLeds,CHSV(120,255,255), CHSV(140,255,bright));
  fill_gradient(ray1b,ray1bLeds,CHSV(120,255,255), CHSV(140,255,bright));
  fill_gradient(ray1c,ray1cLeds,CHSV(120,255,255), CHSV(140,255,bright));
  fill_gradient(ray1d,ray1dLeds,CHSV(120,255,255), CHSV(140,255,bright));
  fill_gradient(ray1e,ray1eLeds,CHSV(120,255,255), CHSV(140,255,bright));

  fill_gradient(ray2a,ray2aLeds,CHSV(120,255,255), CHSV(140,255,bright));
  fill_gradient(ray2b,ray2bLeds,CHSV(120,255,255), CHSV(140,255,bright));
  fill_gradient(ray2c,ray2cLeds,CHSV(120,255,255), CHSV(140,255,bright));
  fill_gradient(ray2d,ray2dLeds,CHSV(120,255,255), CHSV(140,255,bright));
  fill_gradient(ray2e,ray2eLeds,CHSV(120,255,255), CHSV(140,255,bright));  
  EVERY_N_MILLISECONDS(2)
  { 
    if(dir){bright++;}
    if(bright == 175){dir=!dir;};
    if(!dir){bright--;}
    if(bright == 1){dir=!dir;};
  }
  FastLED.show();

  break;

case 8:
  fill_solid(ray1,ray1Leds,CHSV(hueShift,255,255));
  fill_solid(ray2,ray2Leds,CHSV(hueShift,255,255));
  fill_solid(ray3,ray3Leds,CHSV(hueShift,255,255));
  fill_solid(ray4,ray4Leds,CHSV(hueShift,255,255));
  fill_solid(ray5,ray5Leds,CHSV(hueShift,255,255));
  fill_solid(ray6,ray6Leds,CHSV(hueShift,255,255));
  fill_solid(ray7,ray7Leds,CHSV(hueShift,255,255));
  fill_solid(ray8,ray8Leds,CHSV(hueShift,255,255));
  fill_solid(ray9,ray9Leds,CHSV(hueShift,255,255));
  fill_solid(ray10,ray10Leds,CHSV(hueShift,255,255));
  fill_solid(ray11,ray11Leds,CHSV(hueShift,255,255));
  FastLED.show();
  EVERY_N_MILLISECONDS(50){hueShift++;}
  break;
}

}