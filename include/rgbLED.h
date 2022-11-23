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
    void blink(int R, int G, int B, int ms);
    void stopBlink();
    void loop();

  private:
    int _pinR;
    int _pinG;
    int _pinB;

    bool isBlinking;
    bool bl1;

    int R;
    int G;
    int B;

    int ms;
    unsigned long nextBlink;
};

#endif