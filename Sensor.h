//sensor header file
//See gitHub for changes
// Created by: Odin Adema

#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include "Timer.h"
#include "Button.h"

//class Sensors

class Sensor {
    public:
        Sensor(int Links, int Rechts);
        void read();
        bool detectLinks();
        bool detectRechts();
        bool detectTilt();
    private:
        int _Links;
        int _Rechts;
        
};

//constructor

Sensor::Sensor(int Links, int Rechts) {
    _Links = Links;
    _Rechts = Rechts;
    pinMode(_Links, INPUT);
    pinMode(_Rechts, INPUT);
};

void Sensor::read() 
{
    int detectLinks = digitalRead(_Links);
    int detectRechts = digitalRead(_Rechts);
    // Serial.print("Sensor Links: ");
    Serial.print(detectLinks);
    // Serial.print(", Sensor Rechts: ");
    Serial.println(detectRechts);
};


bool Sensor::detectLinks()
{
    int detect = digitalRead(_Links);
    if(detect == LOW){
        Serial.println("Detecting object");
        return true;
    }else{
        return false;
    }
};

bool Sensor::detectRechts()
{
    int detect = digitalRead(_Rechts);
    if(detect == LOW){
        Serial.println("Detecting object");
        return true;
    }else{
        return false;
    }
};



#endif
