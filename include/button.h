/*

  Button.h - Library for detecting Button presses

*/

#ifndef Button_h
#define Button_h

#include "Arduino.h"

class Button 
{
  public:
    Button(int pin);

    bool wasPressed();

  private:
    int _pin;
    static bool buttonWasPressed;

    static void IRAM_ATTR interuptOnPress();
};


#endif