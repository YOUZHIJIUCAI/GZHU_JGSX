#include <Arduino.h>

const int button = 2;
const int LeftSen = 7;
const int RightSen = 8;
const int LeftMotor = 9;
const int RightMotor = 10;
int Sensors = 0;
int GoState = 0;
int count_black = 0;
int threshold_black = 30000;
int count_white = 0;
int threshold_white= 10000;

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
          if(count_white < threshold_white){
            count_white++;
            digitalWrite(LeftMotor,LOW);
            digitalWrite(RightMotor,LOW);
          }else{
            digitalWrite(LeftMotor,HIGH);
            digitalWrite(RightMotor,HIGH);
          }

          count_black = 0;
          break;
        case 0x01:
          digitalWrite(LeftMotor,LOW);
          digitalWrite(RightMotor,HIGH);
          count_white = 0;
          count_black = 0;
          break;       
        case 0x02:
          digitalWrite(RightMotor,LOW);
          digitalWrite(LeftMotor,HIGH);
          count_white = 0;
          count_black = 0;
          break;
        case 0x03:
          if(count_black < threshold_black){
            count_black++;
            digitalWrite(LeftMotor,LOW);
            digitalWrite(RightMotor,LOW);
          }else{
            digitalWrite(LeftMotor,HIGH);
            digitalWrite(RightMotor,HIGH);
          }
          count_white = 0;
          break;
        }
    }
}