/*

  AdminMode.h

*/

#include "Arduino.h"
#include "AdminMode.h"

void AdminMode::sendCrustiAmount()
{
    String antal = String(store.getCrustis());
    pushbullet.push("Crusti Admin", "Antal kvar: " + antal);
}

void AdminMode::setup()
{
    network.init(pushbullet);
    led.blink(0, 0, 255, 1000); // Blink led

    // Create and send a new requsition link
    nordigen.createRequisitionLink(); // Create a new requsition
    pushbullet.push("Requsition link", nordigen.getRequsitionLink())

    // Send amount of crustis left
    sendCrustiAmount();
}

void AdminMode::loop()
{
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
