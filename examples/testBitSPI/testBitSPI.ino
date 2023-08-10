#include <BitSPI.h>

byte MOSI_PIN = 10;
byte MISO_PIN = 11;
byte SCK_PIN = 12;

BitSPI bspi(MOSI_PIN, MISO_PIN, SCK_PIN);

void setup(){
  Serial.begin(9600);
}

void loop(){
  byte data[3];
  for(byte i=0; i<8; i++){
    data[0] = i;
    data[1] = i<<5;
    data[2] = i<<5;
    delay(1000);
    bspi.transfer(&data[0], 14, 5);
  }
}
