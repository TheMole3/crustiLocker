/*

    Motor.h DC Motor controller for Mosfet driver

*/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor 
{
  public:
    // Initialize motor
    Motor(int pin);

    // Start rotation
    void start();

    // Stop rotation
    void stop();

  private:
    int _pin;
};


#endif