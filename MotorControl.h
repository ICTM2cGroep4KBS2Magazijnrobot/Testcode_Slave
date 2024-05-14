//Motor control header file
//See gitHub for changes
// Created by: Odin Adema

#ifndef MotorControl_h
#define MotorControl_h
#include <Arduino.h>
#include "Sensor.h"



//class MotorControl

class MotorControl {
    public:
        MotorControl(int Dir, int PWM, int Brake, int Links, int Rechts, int EncodeA, int EncodeB);
        void move(int richting, int snelheid);
        void read();
        void stop();
        void SetCounter(int counter);
        void PrintCounter();
        int GetCounter();
    private:
        int _Dir;
        int _PWM;
        int _Brake;
        int _Links;
        int _Rechts;
        int _EncodeA;
        int _EncodeB;
        int _Counter;
        Sensor _sensor = Sensor(_Links, _Rechts);

};

//constructor

MotorControl::MotorControl(int Dir, int PWM, int Brake, int Links, int Rechts, int EncodeA, int EncodeB) {
    _Counter = 0;
    _Dir = Dir;
    _PWM = PWM;
    _Brake = Brake;
    _Links = Links;
    _Rechts = Rechts;
    _EncodeA = EncodeA;
    _EncodeB = EncodeB;
    _sensor = Sensor(_Links, _Rechts);
    pinMode(_Dir, OUTPUT);
    pinMode(_PWM, OUTPUT);
    pinMode(_Brake, OUTPUT);
    pinMode(_Links, INPUT_PULLUP);
};



//methodes

void MotorControl::read() 
{
    Serial.print("Motor Direction: ");
    Serial.print(_Dir);
    Serial.print(", Motor PWM: ");
    Serial.print(_PWM);
    Serial.print(", Motor Brake: ");
    Serial.println(_Brake);
};

void MotorControl::move(int richting, int snelheid)
{
    if(richting == 0){
        //move motor to the left
       if (!_sensor.detectLinks()){
            digitalWrite(_Brake, LOW);
            analogWrite(_PWM, snelheid);
            digitalWrite(_Dir, LOW);
       } else {
              stop();
              SetCounter(0);

              
       }
    }else if (richting == 1){
        //move motor to the right
        if (!_sensor.detectRechts()){
            digitalWrite(_Brake, LOW);
            analogWrite(_PWM, snelheid);
            digitalWrite(_Dir, HIGH);
        } else {
            stop();
        }
    }else{
        //stop motor
        stop();
    }
};

void MotorControl::stop()
{
    digitalWrite(_Brake, HIGH);
    analogWrite(_PWM, 0);
};

void MotorControl::SetCounter(int counter){
  _Counter = counter;
}

int MotorControl::GetCounter(){
  return _Counter;
}


void MotorControl::PrintCounter(){
    Serial.println(_Counter);

}




#endif


