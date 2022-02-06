/*

  RGBLED.h - Library for controlling an RGB led

*/


#include "Arduino.h"
#include "RGBLED.h"

RGBLED::RGBLED(int pinR, int pinG, int pinB) 
{
    _pinR = pinR;
    _pinG = pinG;
    _pinB = pinB;

    pinMode(_pinR, OUTPUT);
    pinMode(_pinG, OUTPUT);
    pinMode(_pinB, OUTPUT);
};

void RGBLED::setColor(int R, int G, int B) 
{
    analogWrite(_pinR, R);
    analogWrite(_pinG, G);
    analogWrite(_pinB, B);
};