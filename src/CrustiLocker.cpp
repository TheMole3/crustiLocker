/*

  CrustiLocker.h - Library for detecting CrustiLocker presses

*/

#include "Arduino.h"
#include "CrustiLocker.h"

CrustiLocker::CrustiLocker() {}

void CrustiLocker::setup()
{
    led.setColor(100, 100, 100);
    network.init(pushbullet);

    pushbullet.push("CRUSTI LOCKER STARTED", "");

    led.setColor(0,0,0);
}

int mode = 0;
unsigned long waitUntil = millis();
unsigned long timeout = 0;

bool error = false;

void CrustiLocker::loop()
{
    // If there are no crustis left
    if(crustis <= 0 || error) {

        led.setColor(100, 0, 0);

        if( crustis <= 0 ) pushbullet.push("THERE ARE NO CRUSTIS LEFT", "");
        if( error ) pushbullet.push("CRUSTI LOCKER IS DOWN", "");

        delay(1000*60*60*3); // Loop every 3 hours
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
                timeout = millis() + 1000 * 30 * 1;
            }
        break;

        case 1: // Check for new transactions
            if(millis() >= waitUntil) 
            {
                waitUntil = millis() + 5000;
                if(nordigen.newCrustiTransactionExists(network)) // If there is a new transaction
                {
                    Serial.println("SUCCESSS!!!");
                    // Turn the light solid green
                    led.stopBlink();
                    led.setColor(0, 255, 0);

                    mode = 2; // Go to next step

                    // Dispense crusti
                    IR.wasPressed(); // Clear IR
                    Serial.println("Motor start");
                    motor.start(100);
                }
            }

            // Timeout transaction
            if(millis() >= timeout) 
            {
                led.blink(255, 0, 0, 200);

                timeout = millis() + 10000;
                mode = 3;
            }

        break;

        case 2: // Wait for IR to trigger
            if(IR.wasPressed()) 
            {
                motor.stop();
                Serial.println("Motor stop");
                crustis = store.addCrustis(-1);

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
                error = true;

                // Clear button presses that happened during the transaction search
                button.wasPressed();
                mode = 0; // Return to default mode
            }

        break;
    }

    led.loop();
    
}


