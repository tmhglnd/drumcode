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
#define STRIP_1 3
#define STRIP_2 4
#define STRIP_3 5

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
}

void loop() {
  oscMessageReceiver();
  // short delay to reduce cpu
  // or this can result in missed messages?
  // delay(1);
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
      msgIn.dispatch("/strip/1", ledStripColor<0>);
      msgIn.dispatch("/strip/2", ledStripColor<1>);
      msgIn.dispatch("/strip/3", ledStripColor<2>);
      // blackout a ledstrip completely
      msgIn.dispatch("/strip/1/black", ledStripBlack<0>);
      msgIn.dispatch("/strip/2/black", ledStripBlack<1>);
      msgIn.dispatch("/strip/3/black", ledStripBlack<2>);
    } else {
      // otherwise print error
      Serial.println("Error in OSC Message");
    }
  }
}

// Callback method for variable ledStrip to set the Color
template <int numStrip> void ledStripColor(OSCMessage &msg) {
  // the size of the message
  int size = msg.size();
  // go over every item in the message
  for (int i = 0; i < size; i++){
    // adjust the color for all the LEDs
    // order of values: R G B
    for (int l = 0; l < NUM_LEDS; l++){
      switch(i % 3){
        case 0 : leds[numStrip][l].r = msg.getInt(i);
        case 1 : leds[numStrip][l].g = msg.getInt(i);
        case 2 : leds[numStrip][l].b = msg.getInt(i);
      }
    }
  }
  FastLED.show();
}

// Callback method for blackout of a whole strip
template <int strip> void ledStripBlack(OSCMessage &msg){
  for (int l=0; l<NUM_LEDS; l++){
    leds[strip][l] = CRGB::Black;
  }
  FastLED.show();
}
