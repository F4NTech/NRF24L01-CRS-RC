#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

unsigned int SteerPos, ThruttlePos, BreakPos, PedalPos;

uint8_t address[6] = { "0001"};
int count_r = 0;
bool reverse = false;

//int 
struct RF_MESSAGE {
  int a, b, c;
};

struct MAPPING {
  int p, s;
};

//sender.ino



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
  MAPPING val;
  msg.a = analogRead(A5);
  msg.b = analogRead(A6);
  msg.c = analogRead(A7);

  if (msg.a > 50) {
    count_r = 0;
    reverse = false;
    val.p = map(msg.a, 0 , 457, 1300, 1500);
    Serial.println(msg.a);
  }
  if (msg.b > 100 && msg.a < 100 && count_r == 0) {
    count_r = 1;
    val.p = map(msg.a, 0 , 457, 1400, 1000);
    
  }
  if (count_r == 1 && msg.b < 100 && msg.a < 50) {
    reverse = true;
  }

  if (reverse && msg.b > 100) {
    val.p = map(msg.b, 0 , 520, 1400, 1200);
    Serial.println(msg.b);
  }  
//  Serial.println(count_r );
  val.s =  map(msg.c, 40 , 800, 5, 80);


  bool reports = radio.write(&val, sizeof(val));

  if (reports) {
        Serial.println("success");
//          Serial.println(val.p);
    //      Serial.println(val.b);
//          Serial.println(val.s);
    delay(10);
  } else {
    Serial.println("failed");
  }


}
