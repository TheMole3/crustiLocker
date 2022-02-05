/*

  rgbLED.h - Library for controlling an RGB led

*/

#ifndef rgbLED_h
#define rgbLED_h

#include "Arduino.h"

class rgbLED
{
  public:
    rgbLED(int pinR, int pinG, int pinB);
    void setColor(int R, int G, int B);

  private:
    int _pinR;
    int _pinG;
    int _pinB;
};


#endif