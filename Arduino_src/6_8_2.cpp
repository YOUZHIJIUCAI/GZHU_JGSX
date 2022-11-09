#include <Arduino.h>

const int button = 2;
const int LeftSen = 7;
const int RightSen = 8;
const int LeftMotor = 9;
const int RightMotor = 10;
int Sensors = 0;
int GoState = 0;
byte NSpd = 50;

void setup() {
  // put your setup code here, to run once:
    pinMode(LeftSen,INPUT);
    pinMode(RightSen,INPUT);
    pinMode(button,INPUT_PULLUP);

    pinMode(LED_BUILTIN,OUTPUT);
    pinMode(12,OUTPUT);

    digitalWrite(LeftMotor,255);
    digitalWrite(RightMotor,255);
}

void loop() {
  // put your main code here, to run repeatedly:
    if(digitalRead(button)==LOW){
        while(digitalRead(button)==LOW){
            GoState = !GoState;//切换模式
            digitalWrite(12,!digitalRead(12));
        }
    }
    if(!GoState){
        analogWrite(LeftMotor,255);
        analogWrite(RightMotor,255);
    }
    if(GoState){
        Sensors = (digitalRead(LeftSen) << 1 )|(digitalRead(RightSen) << 0);//LR组合
        switch (Sensors)
        {
        case 0x00:
          analogWrite(LeftMotor,NSpd);
          analogWrite(RightMotor,NSpd);
          break;
        case 0x01:
          analogWrite(LeftMotor,NSpd);
          analogWrite(RightMotor,255);
          break;       
        case 0x02:
          analogWrite(RightMotor,NSpd);
          analogWrite(LeftMotor,255);
          break;
        case 0x03:
          analogWrite(LeftMotor,255);
          analogWrite(RightMotor,255);
          break;
        }
    }
}