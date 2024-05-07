// Headers and libraries
#include <Arduino.h>
#include <Wire.h>
#include "Joystick.h"


// Define the analog pin numbers for the joystick
Joystick joystick(A2, A3, 7);
// Button button(A4);


// Define the state of the button
bool state = LOW;
bool previousState = LOW;
bool werken2 = false;


// Define the byte to receive the data
byte werkenByte = 0;



// Setup function
void setup() {
    Wire.begin(0x08);
    Wire.onReceive(dataRcv);

    // Initialize serial communication
    Serial.begin(115200);
}

void loop()
{
   
    if (werken2 == false) {
        joystick.manualMove(LOW);
    }
    else {
        joystick.manualMove(HIGH);
    }
}

//received data handler function
void dataRcv(int Numbytes){
	while(Wire.available()) {	// read all bytes received
		werken2 = Wire.read() != 0;
	}
}