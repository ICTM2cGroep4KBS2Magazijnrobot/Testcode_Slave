// Headers and libraries
#include <Arduino.h>
#include <Wire.h>
#include "Joystick.h"
#include "MotorControl.h"


const int CLK_PIN = 2;
const int DT_PIN = 6;

int lastClkState = HIGH;
int counter = 0;

MotorControl motorA(12, 3, 9, 10, 0, 7, 6); //vervang 0 door de juiste pin
MotorControl motorB(13, 11, 8, 2, 0, 5, 4); //vervang 0 door de juiste pin

Joystick joystick(A2, A3, 7, motorA, motorB); 
// Button button(A4);


// Define the state of the button
bool state = LOW;
bool previousState = LOW;
bool werken2 = false;


// Define the byte to receive the data
byte werkenByte = 0;



// Setup function


void setup() {
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(CLK_PIN), handleEncoder, CHANGE);

  Serial.begin(9600);

    // Initialize serial communication
}

void loop()
{
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
		werken2 = Wire.read() != 0;
	}
}

void handleEncoder() {
  int clkState = digitalRead(CLK_PIN);
  int dtState = digitalRead(DT_PIN);

  if (clkState != lastClkState) {
    if (dtState != clkState) {
      counter++;
    } else {
      counter--;
    }
  }
  lastClkState = clkState;
  counter = joystick.EncodeTellerA(counter);
}
