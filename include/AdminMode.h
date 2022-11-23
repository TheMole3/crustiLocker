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
    void setup();
    void loop();

    void AdminMode::sendCrustiAmount();

  private:
    Button button = Button(D3);
    Network network;
    Nordigen nordigen = Nordigen();
    RGBLED led = RGBLED(D4, D2, D1);

    Button IR = Button(D6);

    Store store;
    Pushbullet pushbullet = Pushbullet(store.getConfigValue("PUSHBULLET_TOKEN"), store.getConfigValue("PUSHBULLET_CHANNEL"));
};


#endif