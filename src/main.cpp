#include <Arduino.h>

#include "CrustiLocker.h"

CrustiLocker crustiLocker;

void setup() 
{
    Serial.begin(9600);
    
    crustiLocker.setup();
}

// the loop function runs over and over again forever
void loop() 
{
    crustiLocker.loop();
}