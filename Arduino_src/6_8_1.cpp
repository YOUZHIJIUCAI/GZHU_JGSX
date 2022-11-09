#include <Arduino.h>

const int button = 2;
const int LeftSen = 7;
const int RightSen = 8;
const int LeftMotor = 9;
const int RightMotor = 10;
int Sensors = 0;
int GoState = 0;

void setup() {
  // put your setup code here, to run once:
    pinMode(LeftSen,INPUT);
    pinMode(RightSen,INPUT);
    pinMode(button,INPUT_PULLUP);

    pinMode(LED_BUILTIN,OUTPUT);
    pinMode(LeftMotor,OUTPUT);
    pinMode(RightMotor,OUTPUT);

    digitalWrite(LeftMotor,HIGH);
    digitalWrite(RightMotor,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
    if(digitalRead(button)==LOW){
        while(digitalRead(button)==LOW){
            GoState = !GoState;//切换模式
        }
    }
    if(!GoState){
        digitalWrite(LeftMotor,HIGH);
        digitalWrite(RightMotor,HIGH);
    }
    if(GoState){
        Sensors = (digitalRead(LeftSen) << 1 )|(digitalRead(RightSen) << 0);//LR组合
        switch (Sensors)
        {
        case 0x00:
          digitalWrite(LeftMotor,LOW);
          digitalWrite(RightMotor,LOW);
          break;
        case 0x01:
          digitalWrite(LeftMotor,LOW);
          digitalWrite(RightMotor,HIGH);
          break;       
        case 0x02:
          digitalWrite(RightMotor,LOW);
          digitalWrite(LeftMotor,HIGH);
          break;
        case 0x03:
          digitalWrite(LeftMotor,HIGH);
          digitalWrite(RightMotor,HIGH);
          break;
        }
    }
}