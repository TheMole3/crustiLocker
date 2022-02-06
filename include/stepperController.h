/*

  StepperController.h - Library for controlling a stepper motor

*/

#ifndef StepperController_h
#define StepperController_h

#include "Arduino.h"

#include <AccelStepper.h>

class StepperController 
{
  public:
    StepperController (int IN1, int IN2, int IN3, int IN4);

    void rotate(int deg);

    void update();

  private:
    AccelStepper stepper;

    const int stepsPerRevolution = 4096;  // number of steps per revolution of stepper motor
};


#endif