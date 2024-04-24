//sensor header file
// Created by: Odin Adema

#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include "Timer.h"

//class Sensors

class Sensor {
    public:
        Sensor(int Edge, int EncodeA, int EncodeB);
        void read();
        bool detect();
        void counter();
    private:
        int _Edge;
        int _EncodeA;
        int _EncodeB;
        int _counter;
        
};

//constructor

Sensor::Sensor(int Edge, int EncodeA, int EncodeB) {
    _Edge = Edge;
    _EncodeA = EncodeA;
    _EncodeB = EncodeB;
    _counter = 0;
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


void Sensor::counter(){

   

    int stateA = digitalRead(_EncodeA);
    int stateB = digitalRead(_EncodeB);
    if(stateA == HIGH && stateB == LOW){
        _counter++;
    }else if(stateA == LOW && stateB == HIGH){
        _counter--;
    }
    Serial.print("Counter: ");
    Serial.println(_counter);


}




#endif
