// Headers and libraries
#include <Arduino.h>
#include <Wire.h>
#include "Joystick.h"
#include "MotorControl.h"



const int CLK_PIN = 2;
const int DT_PIN = 6;

int lastClkState = HIGH;
int counter = 0;

MotorControl motorA(12, 3, 9, 10, 0, 0, 0); //vervang 0 door de juiste pin
MotorControl motorB(13, 11, 8, 0, 7, 0, 0); //vervang 0 door de juiste pin

Joystick joystick(A2, A3, 7, motorA, motorB); 
// Button button(A4);


// Define the state of the button
bool werken2 = true;


// Define the byte to receive the data
int command; // Received command variable
bool i2cDataReceived = false; // Flag to indicate if I2C data has been received


// Setup function


void setup() {
Wire.begin(0x08);                // join i2c bus with address #8
Wire.onReceive(dataRcv);        // register event
Wire.onRequest(requestEvent); // register event
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(CLK_PIN), handleEncoder, CHANGE);

  Serial.begin(115200);

    // Initialize serial communication
}



void loop()
{ 

    
    if (i2cDataReceived) {
        // Serial.print("Received command: ");
        procesData();
        i2cDataReceived = false;
    }
  
   counter = joystick.EncodePrinterA();
  
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
void requestEvent() {
    // sendData2(counter);
    // sendData("L");
    if (motorA.getdetectLinks() == false)
    {
        // sendData2("L");
        sendData(counter);
        // Serial.println("Links");
    }else{
        // sendData(counter);
        sendData2("L");
    }    
}

void sendData(int data) {
    Wire.write('I');
    Wire.write(data >> 8);
    Wire.write(data & 0xFF);
}

void sendData2(String data2){
    Wire.write('S');
    Wire.write(data2.c_str(), data2.length());
    Serial.println(data2);
    // for (int i = 0; i < data.length(); i++)
    // {
    //     Wire.write(data[i]);
    // }
    
}


void procesData() {
    // Serial.print("Received command: ");  // print "Received command: "
    // Serial.println(command, HEX);  // print the received command in hexadecimal format
    if (command == 0xa1) {  // if the command is 0xa1
        // Serial.println("Zet de motors aan");  // print "Zet de motors aan"
        werken2 = false;  // set werken2 to false
    } else if (command == 0x02) {  // if the command is 0x02
        // Serial.println("Zet de motors uit");  // print "Zet de motors uit"
        werken2 = true;  // set werken2 to true
    } else if (command == 0x20) {
        // Serial.println("Zet de motors aan");  // print "Zet de motors aan"
        werken2 = false;  // set werken2 to false
    } else if(command == 0x10) {
        // Serial.println("Zet de motors uit");  // print "Zet de motors uit"
        werken2 = true;  // set werken2 to true
    }
}
void handleEncoder() {
    int clkState = digitalRead(CLK_PIN);
    int dtState = digitalRead(DT_PIN);

    if (clkState != lastClkState) {
        if (dtState != clkState) {
            counter--;
        } else {
            counter++;
        }
    }
    lastClkState = clkState;
    counter = joystick.EncodeTellerA(counter);
    motorA.SetCounter(counter);
}
