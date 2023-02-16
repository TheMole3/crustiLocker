/*

  AdminMode.h

*/

#include "Arduino.h"
#include "AdminMode.h"

AdminMode::AdminMode(){}

/*
    Sends the current amount of crustis in store to Pushbullet
*/
void AdminMode::sendCrustiAmount()
{
    String antal = String(store.getCrustis());
    pushbullet.push("Crusti Admin", "Antal kvar: " + antal);
}


/*
    Admin mode initialisation
*/
void AdminMode::setup()
{
    network.init(pushbullet);
    led.blink(0, 0, 255, 1000); // Blink led
    
    // Send amount of crustis left
    sendCrustiAmount();
}

void AdminMode::loop()
{
    // Update LED
    led.loop();

    if(button.wasPressed()) // Increment crustis on button press
    {
        int crustis = store.getCrustis();
        crustis++;
        if(crustis > 9) crustis = 0;
        store.setCrustis(crustis);

        sendCrustiAmount();
    }
}
