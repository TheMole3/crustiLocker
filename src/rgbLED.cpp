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
}

void RGBLED::blink(int R, int G, int B, int ms)
{
    this->R = R;
    this->G = G;
    this->B = B;
    this->ms = ms;

    isBlinking = true;
    nextBlink = millis() + ms;

    setColor(R, G, B);
    bl1 = false;
}

void RGBLED::stopBlink()
{
    isBlinking = false;
    setColor(0, 0, 0);
}

void RGBLED::loop()
{
    // Wait until next blink
    if(millis() >= nextBlink && isBlinking) 
    {
        nextBlink = millis() + ms;

        if(bl1) 
        {
            setColor(R, G, B);
        }
        else
        {
            setColor(0, 0, 0);
        }

        bl1 = bl1;
    }
}