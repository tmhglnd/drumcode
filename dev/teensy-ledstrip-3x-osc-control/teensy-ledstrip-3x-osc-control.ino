// 
// Teensy receiving OSC-Messages through W5500 Module
// controlling 3x WS2812B Led Strips with FastLED
// send messages to /strip1 with R G B value 0-255
// send messages to /strip2 with R G B value 0-255
// send messages to /strip3 with R G B value 0-255
// 
// written by Roald van Dillewijn & Timo Hoogland
// for the ./drum.code project
// funded by Creative Industries Fund NL
// 

// Libraries for Ethernet and OSC messages
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCBoards.h>

// Using the FastLED library. More info and help on: https://github.com/FastLED/FastLED
#include <FastLED.h>

// Wiring diagram for W5500 Module 
// connected to Teensy 4.0
// | Name    | Description | Pin |
// | VCC     | Power 3.3V! | 3V  |
// | GND     | Ground      | GND |
// | RST     | Reset       | 9   |
// | CS / SS | Chip Select | 10  |
// | MoSi    | Data out    | 11  |
// | MiSo    | Data in     | 12  |
// | SCLK    | Clock       | 13  |

// Wiring for WS2812B Led Strip:
// Use external power supply 5V 7A (or more depending on the amount of LEDs)
// A WS12812 led ~36mA, so a strip is ~2.16A
// V+ to Red wire
// V- to White wire
// 1000uF Capacitor between V+ and V-, close to led strip connection
// Teensy data pin (3) to Green wire with 470ohm resistor close to led strip

EthernetUDP Udp;

// custom MAC address
byte mac[] = { 0xCA, 0xFE, 0xCA, 0xFE, 0xCA, 0xFE };
// static ip address, make sure laptop and teensy are in the same network!
IPAddress ip(169, 254, 241, 145);
// the port we are using to send to
unsigned int port = 9090;

// this is maybe not needed?
// char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

// How many leds are in the strips
#define NUM_LEDS 60
// How many strips
#define NUM_STRIPS 3
// What pins are connected to the data cables
#define STRIP_1 2
#define STRIP_2 4
#define STRIP_3 6

// create NUM_LEDS with RGB color coding in a 2D array
CRGB leds[NUM_STRIPS][NUM_LEDS];

void setup() {
  Serial.begin(9600);

  // Start the ethernet and udp
  Ethernet.begin(mac, ip);
  Udp.begin(port);
  
  Serial.print("Initialised, IP Address: ");
  Serial.println(Ethernet.localIP());

  // Add LEDS to FastLED, RGB ordering is assumed per LED
  FastLED.addLeds<NEOPIXEL, STRIP_1>(leds[0], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, STRIP_2>(leds[1], NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, STRIP_3>(leds[2], NUM_LEDS);
  Serial.println("LEDs added to FastLED");

  // Initialize all leds black
  for (int s=0; s<NUM_STRIPS; s++){
    for (int l=0; l<NUM_LEDS; l++){
      leds[s][l] = CRGB::Black;
    }
  }
  FastLED.show();
}

void loop() {
  oscMessageReceiver();
  // short delay to reduce cpu
  // or this can result in missed messages?
  delayMicroseconds(1);
}

// A function handling incoming osc messages
void oscMessageReceiver() {
  // get the packet size
  int packetSize = Udp.parsePacket();
  // if any packet received
  if (packetSize > 0) {
    // container for osc-message
    OSCMessage msgIn;
    while (packetSize--)
      // read the message and store
      msgIn.fill(Udp.read());
    if (!msgIn.hasError()) {
      // if no error detected route the message to callback function
      msgIn.dispatch("/strip/1/rgb", ledStripColor<0>);
      msgIn.dispatch("/strip/2/rgb", ledStripColor<1>);
      msgIn.dispatch("/strip/3/rgb", ledStripColor<2>);
      // blackout a ledstrip completely
      msgIn.dispatch("/strip/1/black", ledStripBlack<0>);
      msgIn.dispatch("/strip/2/black", ledStripBlack<1>);
      msgIn.dispatch("/strip/3/black", ledStripBlack<2>);
      // set brightness for white of whole strip
      msgIn.dispatch("/strip/1/white", ledStripWhite<0>);
      msgIn.dispatch("/strip/2/white", ledStripWhite<1>);
      msgIn.dispatch("/strip/3/white", ledStripWhite<2>);
      // set color of the strip based on variable length list of rgbrgbrgb
      msgIn.dispatch("/strip/1/pixel", ledStripRGB<0>);
      msgIn.dispatch("/strip/2/pixel", ledStripRGB<1>);
      msgIn.dispatch("/strip/3/pixel", ledStripRGB<2>);
    } else {
      // otherwise print error
      Serial.println("Error in OSC Message");
    }
  }
}

// Function to set the whole strip to a single Color
template <int strip> void ledStripColor(OSCMessage &msg) {
  // the size of the message
  int size = msg.size();
  // if the message has 3 items (R G B)
  if (size >= 3){
    // adjust the color for all the LEDs
    for (int l=0; l<NUM_LEDS; l++){
      int r = msg.getInt(0);
      int g = msg.getInt(1);
      int b = msg.getInt(2);
      leds[strip][l].setRGB(r, g, b);
    }
    FastLED.show();
  }
}

// Function for setting led color in groups based on
// length of incoming osc-message.
// Sending groups of R G B R G B etc will spread the color
// over the total size of the ledstrip
template <int strip> void ledStripRGB(OSCMessage &msg){
  // the size of the message (should be R G B R G B R G B etc.)
  int size = msg.size();
  // the pixel groupsize based on the total amount divided by size divided by 3
  float groupSize = NUM_LEDS / int(min(size, NUM_LEDS * 3) / 3);
  // go over all the LEDs and adjust the color based on the group
  for (int l=0; l<NUM_LEDS; l++){
    int offset = int(l / groupSize);
    int r = msg.getInt(0 + offset * 3);
    int g = msg.getInt(1 + offset * 3);
    int b = msg.getInt(2 + offset * 3);
    leds[strip][l].setRGB(r, g, b);
  }
  FastLED.show();
}

// Function for blackout of a whole strip
template <int strip> void ledStripBlack(OSCMessage &msg){
  for (int l=0; l<NUM_LEDS; l++){
    leds[strip][l] = CRGB::Black;
  }
  FastLED.show();
}

// Function for controlling white brightness of a whole strip
template <int strip> void ledStripWhite(OSCMessage &msg){
  if (msg.isInt(0)){
    for (int l=0; l<NUM_LEDS; l++){
      int v = msg.getInt(0);
      leds[strip][l].setRGB(v, v, v);
    }
    FastLED.show();
  }
}
