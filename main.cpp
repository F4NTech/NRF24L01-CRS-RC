#include <Arduino.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"

//  Main Transmitter Code


// Radio Declaration
#define CE_PIN 7
#define CSN_PIN 8
RF24 radio(CE_PIN, CSN_PIN);
uint8_t address[6] = { "0001"};
unsigned int count = 1;



void setup() {
  Serial.begin(115200);
  //Radio Setup
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);  // RF24_PA_MAX is default.
  radio.setPayloadSize(32);  // float datatype occupies 32 bytes
  radio.openWritingPipe(address);
  radio.stopListening(); 
  
}

void loop() {
  char msg[16] = "Hello 123";  
  bool report = radio.write(&msg, 32);  // Send msg & save the report
  delay(1000);

  if(report){
    Serial.println("Success sending msg");
    // msg = sizeof(msg) + count;
  }else{
    Serial.println("Failed");
  }
}