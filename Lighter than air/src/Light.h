
void splash() {
  if (!ray3_finished) {
    // Ray3: Chase from end to start (Black, Aqua, Blue, Aqua, Black)
    if (posRay3 >= 2) {
      ray3[posRay3] = CRGB::Black;
      ray3[posRay3 - 1] = CRGB::Aqua;
      ray3[posRay3 - 2] = CRGB::Blue;
      ray3[posRay3 - 3] = CRGB::Aqua;
      if (posRay3 - 4 >= 0) {
        ray3[posRay3 - 4] = CRGB::Black;
      }
      posRay3--;
    } else {
      ray3_finished = true;
      posRay3 = ray3Leds - 1;  // Reset ray3 position for its next cycle
      fill_solid(ray3, ray3Leds, CRGB::Black);
    }
  }

  if (ray3_finished) {
    // Update ray7a, ray7b, ray8a, and ray8b positions and colors
    if (posRay7 < ray7aLeds - 3) {
      ray7a[posRay7] = CRGB::Black;
      ray7a[posRay7 + 1] = CRGB::Aqua;
      ray7a[posRay7 + 2] = CRGB::Blue;
      ray7a[posRay7 + 3] = CRGB::Aqua;
      if (posRay7 + 4 < ray7aLeds) {
        ray7a[posRay7 + 4] = CRGB::Black;
      }
    }
    if (posRay7 < ray7bLeds - 3) {
      ray7b[posRay7] = CRGB::Black;
      ray7b[posRay7 + 1] = CRGB::Aqua;
      ray7b[posRay7 + 2] = CRGB::Blue;
      ray7b[posRay7 + 3] = CRGB::Aqua;
      if (posRay7 + 4 < ray7bLeds) {
        ray7b[posRay7 + 4] = CRGB::Black;
      }
    }

    if (posRay8 < ray8aLeds - 3) {
      ray8a[posRay8] = CRGB::Black;
      ray8a[posRay8 + 1] = CRGB::Aqua;
      ray8a[posRay8 + 2] = CRGB::Blue;
      ray8a[posRay8 + 3] = CRGB::Aqua;
      if (posRay8 + 4 < ray8aLeds) {
        ray8a[posRay8 + 4] = CRGB::Black;
      }
    }
    if (posRay8 < ray8bLeds - 3) {
      ray8b[posRay8] = CRGB::Black;
      ray8b[posRay8 + 1] = CRGB::Aqua;
      ray8b[posRay8 + 2] = CRGB::Blue;
      ray8b[posRay8 + 3] = CRGB::Aqua;
      if (posRay8 + 4 < ray8bLeds) {
        ray8b[posRay8 + 4] = CRGB::Black;
      }
    }

    // Check if ray7a, ray7b, ray8a, and ray8b have reached the end
    if (posRay7 >= ray7aLeds - 3 && posRay7 >= ray7bLeds - 3 && posRay8 >= ray8aLeds - 3 && posRay8 >= ray8bLeds - 3) {
      // Fade ray7a, ray7b, ray8a, and ray8b to black
      if (!fadeStarted) {
        fadeStarted = true;
        fadeCounter = 255;
      }
      for (int i = 0; i < ray7aLeds; i++) {
        ray7a[i].fadeToBlackBy(fadeCounter);
      }
      for (int i = 0; i < ray7bLeds; i++) {
        ray7b[i].fadeToBlackBy(fadeCounter);
      }
      for (int i = 0; i < ray8aLeds; i++) {
        ray8a[i].fadeToBlackBy(fadeCounter);
      }
      for (int i = 0; i < ray8bLeds; i++) {
        ray8b[i].fadeToBlackBy(fadeCounter);
      }

      fadeCounter -= 30;  // Adjust the step size to control the fade speed

      if (fadeCounter < 0) {
        fadeStarted = false;
        posRay7 = 0;
        posRay8 = 0;
        ray3_finished = false;  // Allow ray3 to start its cycle again
        ray5_finished = false;  // Allow ray5 to start its cycle again
      }
    }

    posRay7++;
    posRay8++;
  }

  FastLED.show();
}














void splashRay(CRGB* ray, int rayLeds, int& posRay, bool& rayFinished, bool reverse=false) {
    if (!reverse) {
        if (posRay < rayLeds) {
            if (posRay > 0) ray[posRay - 1] = CRGB::Black; // Turn off the previous LED
            if (posRay % 5 == 0 || posRay % 5 == 4)
                ray[posRay] = CRGB::Aqua;
            else if (posRay % 5 == 2)
                ray[posRay] = CRGB::Blue;
            else
                ray[posRay] = CRGB::Black;
            posRay++;
        } else {
            ray[rayLeds - 1] = CRGB::Black; // Turn off the last LED
            rayFinished = true;
        }
    } else {
        if (posRay >= 0) {
            if (posRay < rayLeds - 1) ray[posRay + 1] = CRGB::Black; // Turn off the previous LED
            if (posRay % 5 == 0 || posRay % 5 == 4)
                ray[posRay] = CRGB::Aqua;
            else if (posRay % 5 == 2)
                ray[posRay] = CRGB::Blue;
            else
                ray[posRay] = CRGB::Black;
            posRay--;
        } else {
            ray[0] = CRGB::Black; // Turn off the last LED
            rayFinished = true;
        }
    }
}
