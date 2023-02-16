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
#include "Motor.h"
#include "Store.h"
#include "Pushbullet.h"

class CrustiLocker
{
  public:
    CrustiLocker();
    void setup();
    void loop();

  private:
    Button button = Button(D3);
    Network network;
    Nordigen nordigen = Nordigen();
    RGBLED led = RGBLED(D4, D2, D1);

    Motor motor = Motor(D5);
    Button IR = Button(D6);

    Store store;
    int crustis = store.getCrustis();

    Pushbullet pushbullet;
};


#endif