#include <Arduino.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"

//  Main Receiver Code


// Radio Declaration :
#define CE_PIN 7
#define CSN_PIN 8
RF24 radio(CE_PIN, CSN_PIN);
uint8_t address[6] = { "0001"};



void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);      // RF24_PA_MAX is default.
  radio.setPayloadSize(32);           // size of payload(MAX)
  radio.openReadingPipe(1, address);  // 
  radio.startListening();             // 
}

void loop() {
  char msg[32] = "";  
  
  if(radio.available()){
  radio.read(&msg, sizeof(msg));  // reading & save the report  
  Serial.println(msg);
  } 
}