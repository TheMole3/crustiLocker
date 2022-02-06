/*

  CrustiLocker.h

*/

#ifndef CrustiLocker_h
#define CrustiLocker_h

#include "Arduino.h"

#include "Button.h"
#include "Network.h"
#include "Nordigen.h"
#include "RGBLED.h"
#include "StepperController.h"
#include "Store.h"

class CrustiLocker
{
  public:
    
    void setup();
    void loop();

  private:
    Button button = Button(D3);
    Network network = Network();
    Nordigen nordigen = Nordigen();
    RGBLED led = RGBLED(D4, D2, D1);
    StepperController stepperMotor = StepperController(D5, D6, D7, D8);
    Store store;
};


#endif