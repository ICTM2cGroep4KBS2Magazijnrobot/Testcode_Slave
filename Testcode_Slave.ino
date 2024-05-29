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

Joystick joystick(A2, A3, 0, motorA, motorB); 
// Button button(A4);


// Define the state of the button
bool werken2 = true;
boolean noodstop = false;
bool automatisch = false;
bool XbewegenRechts = false;
bool XbewegenLinks = false;

bool YbewegenOmhoog = false;
bool YbewegenOmlaag = false;
bool XofY = false; //true = x mag bewegen, false = y mag bewegen

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

  if (noodstop == true){
    motorA.stop();
    motorB.stop();
    joystick.manualMove(HIGH);
  }
    else if (werken2 == false) {
        joystick.manualMove(LOW);
    }
//    else{
//        if(werken2 && XbewegenRechts && XofY){
//          joystick.manualMove(HIGH);
//          motorA.move(1,255); //x as naar rechts
//          XofY = false;
//        }
//        if(werken2 && YbewegenOmhoog && !XofY){
//          joystick.manualMove(HIGH);      
//          motorB.move(0,255); //y as omhoog
//          XofY = true;
//        }
//    }

    else if(werken2 && XbewegenRechts){
      joystick.manualMove(HIGH);
      motorA.move(1,255); //x as naar rechts
    }
    else if(werken2 && XbewegenLinks){
      joystick.manualMove(HIGH);
      motorA.move(0,255);
    }
    else if(werken2 && YbewegenOmhoog){
      joystick.manualMove(HIGH);      
      motorB.move(0,255); //y as omhoog
    }
    else if(werken2 &&YbewegenOmlaag){
      joystick.manualMove(HIGH);
      motorB.move(1,255);
    }
    
    else{
      motorB.stop();
      motorA.stop();
    }
//    else{
//      joystick.manualMove(LOW);
//    }
//    else{
//        joystick.manualMove(HIGH);
//        if(Xbewegen = true){
//          motorA.move(1,255);
//        }
//        else{
//          motorA.stop();
//        }
//        if(Ybewegen = true){
//          motorB.move(1,255);
//        }
//        else{
//          motorB.stop();
//        }
//    }
}


//received data handler function
void dataRcv(int Numbytes){
	while(Wire.available()) {	// read all bytes received
		command = Wire.read();
        i2cDataReceived = true;
	}
}
// void requestEvent() { 
//         int reset1 = digitalRead(10);
//         Serial.println(reset1);
//         // Serial.println("Request event");
//         // Serial.println(counter);
//         sendData(10,counter);
//         sendData(20, reset1); 
// }

void requestEvent() { 
    int reset1 = digitalRead(10);
    int reset2 = digitalRead(7);
//    Serial.println(reset2);
    if (reset1 == 0){
        counter = 0;
        sendData(10,counter);
    }else if (reset2 == 0){
        sendData(20, 0);
    }else if(reset1 == 1 && reset2 == 1){
        // sendData(20, 1);
        sendData(10,counter);
        sendData(20, 0);
    }
    
    // sendData(10,counter);
    // sendData(20, reset1);
}

void sendData(int id, int data) {
    Wire.write(id);
    Wire.write(data >> 8);
    // Serial.println(data >> 8);
    Wire.write(data & 0xFF);
    // Serial.println(data & 0xFF);
}



void procesData() {
    // Serial.print("Received command: ");  // print "Received command: "
    // Serial.println(command, HEX);  // print the received command in hexadecimal format
    if (command == 0xa1) {  // if the command is 0xa1
        // Serial.println("Zet de motors aan");  // print "Zet de motors aan"
        noodstop = false;
        werken2 = false;  // set werken2 to false
    } else if(command == 0x11){
       noodstop = true;
    } else if (command == 0x02) {  // if the command is 0x02
        // Serial.println("Zet de motors uit");  // print "Zet de motors uit"
        noodstop = false;
        werken2 = true;  // set werken2 to true
    } else if (command == 0x20) {
        // Serial.println("Zet de motors aan");  // print "Zet de motors aan"
        noodstop = false;
        werken2 = false;  // set werken2 to false
    } else if(command == 0x10) {
        // Serial.println("Zet de motors uit");  // print "Zet de motors uit"
        noodstop = false;
        werken2 = true;  // set werken2 to true
    } 
    else if(command == 0x66){
      noodstop = false;
      werken2 = true;
      XbewegenRechts = true; //laat x as naar rechts bewegen
    } else if(command == 0x67){
      noodstop = false;
      werken2 = true;
      XbewegenRechts = false; //laat x as stoppen met bewegen
    } else if(command == 0x68){
      noodstop = false;
      werken2 = true;
      YbewegenOmhoog = true;
    } else if(command == 0x69){
      noodstop = false;
      werken2 = true;
      YbewegenOmhoog = false;
    } else if(command == 0x70){
      noodstop = false;
      werken2 = true;
      XbewegenLinks = true;
    } else if(command == 0x71){
      noodstop = false;
      werken2 = true;
      XbewegenLinks = false;
    } else if(command == 0x72){
      noodstop = false;
      werken2 = true;
      YbewegenOmlaag = true;
    } else if(command == 0x73){
      noodstop = false;
      werken2 = true;
      YbewegenOmlaag = false;;
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
