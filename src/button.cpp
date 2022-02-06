/*

  Button.h - Library for detecting button presses

*/

#include "Arduino.h"
#include "Button.h"

bool Button::buttonWasPressed = false;

Button::Button(int pin)
{
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), interuptOnPress, RISING);
};

bool Button::wasPressed() 
{
    bool status = buttonWasPressed;
    this->buttonWasPressed = false;
    return status;
}

void IRAM_ATTR Button::interuptOnPress()
{
    Button::buttonWasPressed = true;
}