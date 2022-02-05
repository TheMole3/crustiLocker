/*

  stepperController.h - Library for controlling a stepper motor

*/

#include "Arduino.h"
#include "stepperController.h"

stepperController::stepperController(int IN1, int IN2, int IN3, int IN4) 
{
    this->stepper = AccelStepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

    // set the speed and acceleration
    stepper.setMaxSpeed(500);
    stepper.setAcceleration(100);
};

void stepperController::rotate(int deg) 
{
    long currentPos = stepper.currentPosition();
    stepper.moveTo(currentPos + (deg/360)*stepsPerRevolution);
}

void stepperController::update() 
{
    if (stepper.distanceToGo() != 0) // If the stepper is not at its target position
    { 
        stepper.run();
    }  
};