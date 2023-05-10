  #include <Servo.h>

#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#define CE_PIN 7
#define CSN_PIN 8


Servo Steer;
Servo Pedal;
//Servo Break;

// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

uint8_t address[6] = { "0001"};
float payload = 0.0;

// Declaration Servo pos
unsigned int SteerPos, ThruttlePos, BreakPos, PedalPos;
bool Reverse = false;
int count_reverse = 0;


struct RF_MESSAGE {
  int a, b;  
};


void setup() {
  Serial.begin(115200);
  
  Steer.attach(4);                                      // Servo Steer setpin
  Pedal.attach(5);                                  // Servo Throttle setpin  
//  Break.attach(6);                                     // Servo Break setpin
  
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);        // RF24_PA_MAX is default.
  radio.setPayloadSize(32);                      // float datatype occupies 32 bytess
  radio.openReadingPipe(1, address);     // Open reading mode to Address
  radio.startListening();                             // Start listening msg

}

void loop() {
//  char msg[32] = "";
  if (radio.available()) {
    RF_MESSAGE msg;    

    
    radio.read(&msg, sizeof(msg));
    Serial.println(F("Message received:"));
    Serial.println(msg.a);
    Serial.println(msg.b);   
    Pedal.write( msg.a);
    
//    ThruttlePos= map(msg.a, 0 ,457, 1350, 1450); 
//    BreakPos = map(msg.b, 0 ,515, 1250, 1200);
//    SteerPos=  map(msg.c, 40 ,800, 5, 80);    
    
//    Serial.println(ThruttlePos);    
//    Serial.println(BreakPos);    
//    Serial.println(SteerPos);    
//    PedalPos = map(PedalPos, BreakPos, ThruttlePos, BreakPos);
//    Serial.println("");
//    Serial.println(ThruttlePos ^ BreakPos );
    
//    Steer.write(SteerPos);

//    return msg;
  }

}
