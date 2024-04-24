//Motor control header file
// Created by: Odin Adema

#ifndef MotorControl_h
#define MotorControl_h
#include <Arduino.h>
#include "Sensor.h"



//class MotorControl

class MotorControl {
    public:
        MotorControl(int Dir, int PWM, int Brake, int Links, int EncodeA, int EncodeB);
        void move(int richting, int snelheid);
        void read();
        void stop();
        bool detect();
    private:
        int _Dir;
        int _PWM;
        int _Brake;
        int _Links;
};

//constructor

MotorControl::MotorControl(int Dir, int PWM, int Brake, int Links, int EncodeA, int EncodeB) {
    Sensor sensorA(Links, EncodeA, EncodeB);
    _Dir = Dir;
    _PWM = PWM;
    _Brake = Brake;
    _Links = Links;
    pinMode(_Dir, OUTPUT);
    pinMode(_PWM, OUTPUT);
    pinMode(_Brake, OUTPUT);
    pinMode(_Links, INPUT_PULLUP);
}

//methodes

void MotorControl::read() 
{
    Serial.print("Motor Direction: ");
    Serial.print(_Dir);
    Serial.print(", Motor PWM: ");
    Serial.print(_PWM);
    Serial.print(", Motor Brake: ");
    Serial.println(_Brake);
}

void MotorControl::move(int richting, int snelheid)
{
    Serial.print("Motor Direction: ");
    Serial.println(richting);
    if(richting == 0){
        //move motor to the left
       if (!detect()){
            digitalWrite(_Brake, LOW);
            analogWrite(_PWM, snelheid);
            digitalWrite(_Dir, LOW);
       } else {
           stop();
       }
    }else if (richting == 1){
        //move motor to the right{
            digitalWrite(_Brake, LOW);
            analogWrite(_PWM, snelheid);
            digitalWrite(_Dir, HIGH);
    }else{
        //stop motor
        stop();
    }
}

void MotorControl::stop()
{
    digitalWrite(_Brake, HIGH);
    analogWrite(_PWM, 0);
}

bool MotorControl::detect()
{
    int detect = digitalRead(_Links);
    if(detect == LOW){
        Serial.println("Detecting object");
        return true;
    }else{
        return false;
    }
}



#endif


