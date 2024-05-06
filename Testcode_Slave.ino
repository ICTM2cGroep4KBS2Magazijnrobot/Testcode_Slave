// Headers and libraries
#include <Arduino.h>
#include "Joystick.h"


// Define the analog pin numbers for the joystick
Joystick joystick(A2, A3, 7);
Button button(8);

// Setup function
void setup() {
    // Initialize serial communication
    Serial.begin(115200);
}

void loop()
{
    
    if (button.getState() == HIGH)
    {
        joystick.manualMove();
    }
    else if (button.getState() == LOW)
    {
        motorA.stop();
        motorB.stop();
    }

}