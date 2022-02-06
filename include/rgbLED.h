/*

  RGBLED.h - Library for controlling an RGB led

*/

#ifndef RGBLED_h
#define RGBLED_h

#include "Arduino.h"

class RGBLED
{
  public:
    RGBLED(int pinR, int pinG, int pinB);
    void setColor(int R, int G, int B);

  private:
    int _pinR;
    int _pinG;
    int _pinB;
};


#endif