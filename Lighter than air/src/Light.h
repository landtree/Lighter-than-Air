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

  FastLED.show();
}
