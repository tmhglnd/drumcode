// 
// Teensy receiving OSC-Messages through W5500 Module
// controlling a WS2812B Led Strip with FastLED
// send message /color with R G B value 0-255
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

// How many leds are in the strip
#define NUM_LEDS 60
// What pin is connected to the data cable
#define STRIP_1 3

// create NUM_LEDS with RGB color coding
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);

  // Start the ethernet and udp
  Ethernet.begin(mac, ip);
  Udp.begin(port);
  
  Serial.print("Initialised, IP Address: ");
  Serial.println(Ethernet.localIP());

  // Add LEDS to FastLED, RGB ordering is assumed per LED
  FastLED.addLeds<NEOPIXEL, STRIP_1>(leds, NUM_LEDS);
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
      msgIn.route("/color", colorReceiver);
    } else {
      // otherwise print error
      Serial.println("Error in OSC Message");
    }
  }
}

// Callback method when "/color" received
void colorReceiver(OSCMessage &msg, int addrOffset) {
  // the size of the message
  int size = msg.size();
  // go over every item in the message
  for (int i = 0; i < size; i++){
    // adjust the color for all the LEDs
    // order of values: R G B
    for (int l = 0; l < NUM_LEDS; l++){
      switch(i % 3){
        case 0 : leds[l].r = msg.getInt(i);
        case 1 : leds[l].g = msg.getInt(i);
        case 2 : leds[l].b = msg.getInt(i);
      }
    }
  }
  // update the LEDs
  FastLED.show();
}
