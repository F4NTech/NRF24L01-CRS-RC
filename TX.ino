#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

uint8_t address[6] = { "0001"};


struct RF_MESSAGE {
  int a, b, c;  
};

//sender.ino
//#include "global.h"


void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);  // RF24_PA_MAX is default.
  radio.setPayloadSize(32);  // float datatype occupies 4 bytes
  radio.openWritingPipe(address);
  radio.stopListening(); 

}

void loop() {
RF_MESSAGE msg;
msg.a = analogRead(A0);
msg.b = analogRead(A1);
msg.c = analogRead(A2);

bool reports = radio.write(&msg, sizeof(msg));

if(reports){
  Serial.println("success");
  Serial.println(msg.a);
  Serial.println(msg.b);
  Serial.println(msg.c);
  delay(10);
}else{
  Serial.println("failed");
}


}
