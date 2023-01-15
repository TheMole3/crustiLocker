#include <Arduino.h>

#include "CrustiLocker.h"
#include "AdminMode.h"
#include "Store.h"

/*
CrustiLocker crustiLocker;
AdminMode adminMode;

Motor motor = Motor(D5);


bool adminModeEnabled = false;

void setup() 
{
    Serial.begin(9600);
    Serial.println("\n\n ");
    
    // If the admin button is pressed
    pinMode(D7, INPUT);
    
    //adminModeEnabled = digitalRead(D7);
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

}*/



/*
 Interfacing Arduino IR Sensor Module
 https://www.bristolwatch.com/arduino/arduino_ir.htm
 by Lewis Loflin lewis@bvu.net
*/


int Led = D1 ;// define LED Interface
int buttonpin = D6; // define the obstacle avoidance sensor interface

void setup ()
{
  pinMode (Led, OUTPUT) ;// define LED as output interface
  pinMode (buttonpin, INPUT) ;// define the obstacle avoidance sensor output interface
}
void loop ()
{
  if (digitalRead (buttonpin) == HIGH) // When the obstacle avoidance sensor detects a signal, LED goes on.
  {
    digitalWrite (Led, HIGH);
  }
  else
  {
    digitalWrite (Led, LOW);
  }
}