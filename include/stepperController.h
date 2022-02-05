/*

  stepperController.h - Library for controlling a stepper motor

*/

#ifndef stepperController_h
#define stepperController_h

#include "Arduino.h"

#include <AccelStepper.h>

class stepperController 
{
  public:
    stepperController (int IN1, int IN2, int IN3, int IN4);

    void rotate(int deg);

    void update();

  private:
    AccelStepper stepper;

    const int stepsPerRevolution = 4096;  // number of steps per revolution of stepper motor
};


#endif