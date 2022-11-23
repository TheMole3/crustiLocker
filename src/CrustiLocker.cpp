/*

  CrustiLocker.h - Library for detecting CrustiLocker presses

*/

#include "Arduino.h"
#include "CrustiLocker.h"

void CrustiLocker::setup()
{
    network.init(pushbullet);
}

int mode = 0;
unsigned long waitUntil = millis();
unsigned long timeout = 0;

void CrustiLocker::loop()
{
    // If there are no crustis left
    if(store.getCrustis() >= 0) {
        led.setColor(255, 0, 0);
        return;
    } 

    switch(mode) 
    {
        default: // Wait for button press
            if(button.wasPressed()) 
            {
                mode = 1; // Go to next step
                led.blink(255, 100, 0, 1000); // Blink led yellow

                // Set transaction timeout
                timeout = millis() + 1000 * 60 * 1;
            }

        break;

        case 1: // Check for new transactions
            if(millis() >= waitUntil) 
            {
                waitUntil = millis() + 5000;
                if(nordigen.newCrustiTransactionExists(network)) // If there is a new transaction
                {
                    // Turn the light solid green
                    led.stopBlink();
                    led.setColor(0, 255, 0);

                    mode = 2; // Go to next step

                    // Dispense crusti
                    motor.start(100);
                }
            }

            // Timeout transaction
            if(millis() >= timeout) 
            {
                led.blink(255, 0, 0, 500);

                timeout = millis() + 5000;
                mode = 3;
            }

        break;

        case 2: // Wait for IR to trigger
            if(IR.wasPressed()) 
            {
                motor.stop();
                store.addCrustis(-1);

                led.setColor(0, 0, 0);

                // Clear button presses that happened during the transaction search
                button.wasPressed();
                mode = 0; // Return to default mode
            }

        break;

        case 3: // Clear error
            if(millis() >= timeout) 
            {
                led.stopBlink();

                // Clear button presses that happened during the transaction search
                button.wasPressed();
                mode = 0; // Return to default mode
            }

        break;
    }

    led.loop();
}


