// Headers and libraries
#include <Arduino.h>
#include "Joystick.h"


// Define the analog pin numbers for the joystick
Joystick joystick(A2, A3, 7);
Button button(A4);
bool state = LOW;
bool previousState = LOW;
bool werken = false;



// Setup function
void setup() {
    // Initialize serial communication
    Serial.begin(115200);
}

void loop()
{
    Serial.print(button.getState());
    Serial.print(" : ");
    // Get the state of the button
    state = button.getState();
    // Check if the button is pressed
    if (state == HIGH && previousState == LOW) {
        // Print a message
        Serial.println("Button pressed");
        werken = !werken;

    }
    // Update the previous state
    previousState = state;
    Timer(millis(), 100);

    Serial.println(werken);
    if (werken == false) {
        joystick.manualMove(LOW);
    }
    else {
        joystick.manualMove(HIGH);
    }
}
