
// Using the FastLED library. More info and help on: https://github.com/FastLED/FastLED
#include <FastLED.h>

// Wiring for WS2812B Led Ring:
// A WS12812 led ~36mA, so a ring of 16 is ~0.58A
// V+ to Red wire
// V- to White wire
// 1000uF Capacitor between V+ and V-, close to led strip connection
// ESP32 data pin (1) to yellow wire with 470ohm resistor close to led ring

// Wiring for pushbutton to switch light schemes:
// Using a 10kOhm resistor for pull-down
// V+ to bottomleft button leg
// bottomright button leg to resistor
// resistor to V-
// 

// How many leds are in the ring
#define NUM_LEDS 16
// What pin is connected to the data cable
#define RING 1

// create NUM_LEDS with RGB color coding in a 1D array
CRGB leds[NUM_LEDS];

// Pin for pushbutton
#define BTN_PIN 10

// Some variables for debouncing the button press
unsigned long debounceTime = 10;
unsigned long lastDebounce = 0;

void setup() {
  Serial.begin(9600);

  Serial.println("Initialised");

  // Add LEDS to FastLED, RGB ordering is assumed per LED
  FastLED.addLeds<NEOPIXEL, RING>(leds, NUM_LEDS);
  Serial.println("LEDs added to FastLED");
}

// the scene/program counter
int programCount = 0;
int numPrograms = 4;
int btnState = LOW;
int _btnState = LOW;

// various scenes based on 2 colors { r, g, b, r2, g2, b2 }
int scene1[] = { 255, 255, 255, 20, 20, 20 };
int scene2[] = { 0, 255, 66, 0, 98, 255 };
int scene3[] = { 255, 26, 29, 193, 27, 242 };

void loop() {
  // current reading from digital pin
  int reading = digitalRead(BTN_PIN);

  // reset the debounce timer
  if (reading != _btnState){
    lastDebounce = millis();
  }

  // Detect a buttonpress and increment the light program
  // if the time is greater than the debounceTime
  if (millis() - lastDebounce > debounceTime){
    // if the reading is not the current state
    if (reading != btnState){
      btnState = reading;
      // if btnState also equals HIGH increment the program
      if (btnState == HIGH){
        programCount = (programCount + 1) % numPrograms;
      }
    }
  }

  // store the current reading in previous state
  _btnState = reading;

  if (programCount == 0){
    // turn of all the LEDs in program 0
    for (int l = 0; l < NUM_LEDS; l++){ 
      leds[l] = CRGB::Black;
    }
  }

  // for all the colors 
  else if (programCount == 1){
    lightProgram(scene1, 105);
  }

  else if (programCount == 2){
    lightProgram(scene2, 126);
  }

  else if (programCount == 3){
    lightProgram(scene3, 134);
  }

  // create a hue rotation of the color over all the LEDs based on milliseconds
  // else if (programCount == 1){
  //   for (int l = 0; l < NUM_LEDS; l++){
  //     leds[l] = CHSV(millis() / 36, 255, 255);
  //   }
  // }

  // display the colors
  FastLED.show();

  // short delay
  delay(5);
}

// run light program interpolating between 2 colors over 1 bar at given bpm
void lightProgram(int scene[], float bpm){
  float t = millis() / (240000 * 4 / bpm);
  // calculate interpolation factor for crossfade between 2 colors
  float i = cos(t * TWO_PI) * 0.5 + 0.5;

  // for every color in the list (R G B) calculate the interpolation
  for (int c = 0; c < 3; c++){
    int color = scene[c] * (1 - i) + scene[c+3] * i;
    // set the calculated color for all LEDs
    for (int l = 0; l < NUM_LEDS; l++){
      leds[l][c] = color;
    }
  }
}
