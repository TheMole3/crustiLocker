/*

  IR.h - Library for detecting IR presses

*/

#ifndef IR_h
#define IR_h

#include "Arduino.h"

class IR 
{
  public:
    IR(int pin, int enablePin);

    bool wasPressed();
    void loop();

  private:
    int _pin;
    int _enablePin;
    bool objectDetect;

};


#endif