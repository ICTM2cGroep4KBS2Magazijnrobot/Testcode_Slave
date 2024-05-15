// Headers and libraries
#include <Arduino.h>
#include <Wire.h>
#include "Joystick.h"


// Define the analog pin numbers for the joystick
Joystick joystick(A2, A3, 7, motorA, motorB);
MotorControl motorA(12, 3, 9, 10, 0, 7, 6); //vervang 0 door de juiste pin
MotorControl motorB(13, 11, 8, 2, 0, 5, 4); //vervang 0 door de juiste pin

// Define the button pin number


// Define the state of the button
bool werken2 = true;


// Define the byte to receive the data
int command; // Received command variable
bool i2cDataReceived = false; // Flag to indicate if I2C data has been received


// Setup function
void setup() {
    Wire.begin(0x08);
    Wire.onReceive(dataRcv);

    // Initialize serial communication
    Serial.begin(115200);
}



void loop()
{
    if (i2cDataReceived) {
        Serial.print("Received command: ");
        procesData();
        i2cDataReceived = false;
    }
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
		command = Wire.read();
        i2cDataReceived = true;
	}
}

void procesData() {
    Serial.print("Received command: ");  // print "Received command: "
    Serial.println(command, HEX);  // print the received command in hexadecimal format
    if (command == 0xa1) {  // if the command is 0xa1
        Serial.println("Zet de motors aan");  // print "Zet de motors aan"
        werken2 = false;  // set werken2 to false
    } else if (command == 0x02) {  // if the command is 0x02
        Serial.println("Zet de motors uit");  // print "Zet de motors uit"
        werken2 = true;  // set werken2 to true
    } else if (command == 0x20) {
        Serial.println("Zet de motors aan");  // print "Zet de motors aan"
        werken2 = false;  // set werken2 to false
    } else if(command == 0x10) {
        Serial.println("Zet de motors uit");  // print "Zet de motors uit"
        werken2 = true;  // set werken2 to true
    }
}