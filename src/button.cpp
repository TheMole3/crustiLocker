/*

  button.h - Library for detecting button presses

*/

#include "Arduino.h"
#include "button.h"

bool button::buttonWasPressed = false;

button::button(int pin)
{
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), interuptOnPress, RISING);
};

bool button::wasPressed() 
{
    bool status = buttonWasPressed;
    this->buttonWasPressed = false;
    return status;
}

void IRAM_ATTR button::interuptOnPress()
{
    button::buttonWasPressed = true;
}