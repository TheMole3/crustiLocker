/*

  button.h - Library for detecting button presses

*/

#ifndef button_h
#define button_h

#include "Arduino.h"

class button 
{
  public:
    button(int pin);

    bool wasPressed();

  private:
    int _pin;
    static bool buttonWasPressed;

    static void IRAM_ATTR interuptOnPress();
};


#endif