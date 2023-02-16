#include <Arduino.h>

#include "CrustiLocker.h"
#include "AdminMode.h"
#include "Store.h"


CrustiLocker crustiLocker;
AdminMode adminMode;

Motor motor = Motor(D5);


bool adminModeEnabled = false;

void setup() 
{
    Serial.begin(9600);
    Serial.println("\n\n ");
    
    // If the admin button is pressed on startup start adminMode
    pinMode(D7, INPUT);
    adminModeEnabled = digitalRead(D7);

    if(adminModeEnabled) 
    {
        Serial.println("Admin mode");
        adminMode.setup();
    }
    else
    {
        Serial.println("Normal mode");
        crustiLocker.setup();
    }

}

// The loop function runs over and over again forever
void loop() 
{
    if(adminModeEnabled) 
    {
        adminMode.loop();
    }
    else
    {
        crustiLocker.loop();
    }

}