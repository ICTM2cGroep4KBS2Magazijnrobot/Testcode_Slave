//sensor header file
// Created by: Odin Adema

#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>

//class Sensors

class Sensor {
    public:
        Sensor(int Edge, int EncodeA, int EncodeB);
        void read();
        bool detect();
    private:
        int _Edge;
        int _EncodeA;
        int _EncodeB;
};

//constructor

Sensor::Sensor(int Edge, int EncodeA, int EncodeB) {
    _Edge = Edge;
    _EncodeA = EncodeA;
    _EncodeB = EncodeB;
    pinMode(_Edge, INPUT);
    pinMode(_EncodeA, INPUT);
    pinMode(_EncodeB, INPUT);
}


bool Sensor::detect()
{
    int detect = digitalRead(_Edge);
    if(detect == LOW){
        Serial.println("Detecting object");
        return true;
    }else{
        return false;
    }
}




#endif
