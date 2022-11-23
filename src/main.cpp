#include <Arduino.h>

#include "CrustiLocker.h"
#include "AdminMode.h"

CrustiLocker crustiLocker;
AdminMode adminMode;

bool adminModeEnabled = false;

void setup() 
{
    Serial.begin(9600);
    
    // If the admin button is pressed
    adminModeEnabled = digitalRead(D7);
    if(adminModeEnabled) 
    {
        adminMode.setup();
    }
    else
    {
        crustiLocker.setup();
    }

}

// the loop function runs over and over again forever
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