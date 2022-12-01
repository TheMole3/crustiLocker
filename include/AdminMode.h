/*

  AdminMode.h

*/

#ifndef AdminMode_h
#define AdminMode_h

#include "Arduino.h"

#include "Button.h"
#include "Network.h"
#include "Nordigen.h"
#include "RGBLED.h"
#include "Store.h"
#include "Pushbullet.h"

class AdminMode
{
  public:
    AdminMode();
    void setup();
    void loop();

    void sendCrustiAmount();

  private:
    Button button = Button(D3);
    Network network;
    Nordigen nordigen = Nordigen();
    RGBLED led = RGBLED(D4, D2, D1);

    Button IR = Button(D6);

    Store store;
    Pushbullet pushbullet;
};


#endif