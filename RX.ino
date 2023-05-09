#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

uint8_t address[6] = { "0001"};
float payload = 0.0;

struct RF_MESSAGE {
  int a, b, c;  
};


void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);  // RF24_PA_MAX is default.
  radio.setPayloadSize(32);  // float datatype occupies 32 bytess
  radio.openReadingPipe(1, address);
  radio.startListening();

}

void loop() {
  char msg[32] = "";
  if (radio.available()) {
    RF_MESSAGE msg;
    radio.read(&msg, sizeof(msg));
    Serial.println(F("Message received:"));
    Serial.println(msg.a);
    Serial.println(msg.b);
    Serial.println(msg.c);
  }
  else{
//    Serial.println("not Available");
  }

}
