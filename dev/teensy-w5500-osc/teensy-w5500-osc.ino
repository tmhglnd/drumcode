
// Libraries for Ethernet and OSC messages
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCBoards.h>

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

void setup() {
  Serial.begin(9600);

  Ethernet.begin(mac, ip);
  Udp.begin(port);
  
  Serial.print("Initialised, IP Address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  oscMessageReceiver();
  // short delay to reduce cpu
  delay(10);
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
      msgIn.route("/test", testReceived);
    } else {
      // otherwise print error
      Serial.println("Error in OSC Message");
    }
  }
}

// Callback method when "/test" received
void testReceived(OSCMessage &msg, int addrOffset) {
  Serial.print("Received: ");
  // the size of the message
  int size = msg.size();
  // go over every item in the message
  for (int i = 0; i < size; i++){
    Serial.print(msg.getInt(i));
    Serial.print(" ");
  }
  Serial.println();
}
