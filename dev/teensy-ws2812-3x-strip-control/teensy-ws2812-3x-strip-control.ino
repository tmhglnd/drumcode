// 
// Teensy controlling 3x WS2812B Led Strip
// A study on how to connect multiple Led Strips
// 
// written by Roald van Dillewijn & Timo Hoogland
// for the ./drum.code project
// funded by Creative Industries Fund NL
// 

// Using the FastLED library. More info and help on: https://github.com/FastLED/FastLED
#include <FastLED.h>

// How many leds are in the strips
// define multiple if lengths differ per strip
#define NUM_LEDS 60
// What pins are connected to the data cables
#define STRIP_1 3
#define STRIP_2 4
#define STRIP_3 5

// create NUM_LEDS with RGB color coding
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);

  // Add LEDS to FastLED, RGB ordering is assumed per LED
  FastLED.addLeds<NEOPIXEL, STRIP_1>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, STRIP_2>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, STRIP_3>(leds, NUM_LEDS);
}

// loop counter
int count = 0;

void loop() {
  // Go over all the LEDS and display a Color
  for (int i = 0; i < NUM_LEDS; i++){
    // change the color R, G, B, W based on loop count
    switch (count % 4){
      case 0 : leds[i].setRGB(255, 0, 0); break;
      case 1 : leds[i].setRGB(0, 255, 0); break;
      case 2 : leds[i].setRGB(0, 0, 255); break;
      case 3 : leds[i].setRGB(255, 255, 255); break;
    }
    FastLED.show();

    // set the LED to Black
    leds[i] = CRGB::Black;

    // delay in the loop to create a moving dot on the strip
    delay(30);
  }
  // count the cycles to change the color
  count++;
}
