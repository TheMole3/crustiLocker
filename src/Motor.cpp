/*

    DC Motor controller for Mosfet driver

*/

#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int pin)
{
    _pin = pin;
    pinMode(pin, OUTPUT);
};

void Motor::start(int speed)
{
    analogWrite(_pin, speed);
}

void Motor::stop()
{
    analogWrite(_pin, 0);
}