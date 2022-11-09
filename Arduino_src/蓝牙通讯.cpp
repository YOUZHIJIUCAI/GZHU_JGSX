#include <Arduino.h>

byte GoState = 0;
byte monitor = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
}

void loop() {
  if(Serial.available()){
    switch (Serial.read())
    {
    case 'g':
      GoState = 1;
      Serial.write("GO");
      break;
    case 's':
      GoState = 0;
      Serial.write("stop");
      break;
    case 'y':
      Serial.print("monitorstart");
      monitor = 1;
      break;
    case 'n':
      monitor = 0;
      Serial.print("monitorstop");
      break;
    }
  }
}