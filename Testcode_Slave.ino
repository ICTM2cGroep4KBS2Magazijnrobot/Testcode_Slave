// Headers and libraries
#include <Arduino.h>
#include "Joystick.h"


// Define the analog pin numbers for the joystick
Joystick joystick(A2, A3, 7);




// Setup function
void setup() {
    // Initialize serial communication
    Serial.begin(9600);
}

void loop()
{
    
    //joystick.read();
    joystick.manualMove();

}