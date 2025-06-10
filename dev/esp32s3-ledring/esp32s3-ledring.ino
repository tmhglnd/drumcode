
// Using the FastLED library. More info and help on: https://github.com/FastLED/FastLED
#include <FastLED.h>

// Wiring for WS2812B Led Ring:
// A WS12812 led ~36mA, so a ring of 16 is ~0.58A
// V+ to Red wire
// V- to White wire
// 1000uF Capacitor between V+ and V-, close to led strip connection
// ESP32 data pin (1) to yellow wire with 470ohm resistor close to led ring

// How many leds are in the ring
#define NUM_LEDS 16
// What pin is connected to the data cable
#define RING 1

// create NUM_LEDS with RGB color coding in a 1D array
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);

  Serial.println("Initialised");

  // Add LEDS to FastLED, RGB ordering is assumed per LED
  FastLED.addLeds<NEOPIXEL, RING>(leds, NUM_LEDS);
  Serial.println("LEDs added to FastLED");
}

int programCount = 0;

void loop() {
  // create a hue rotation of the color over all the LEDs
  // based on milliseconds
  for (int l = 0; l < NUM_LEDS; l++){
    leds[l] = CHSV(millis() / 5, 255, 255);
  }
  FastLED.show();

  // short delay
  delay(5);
}
