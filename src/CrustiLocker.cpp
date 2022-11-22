/*

  CrustiLocker.h - Library for detecting CrustiLocker presses

*/

#include "Arduino.h"
#include "CrustiLocker.h"

void CrustiLocker::setup()
{
  network.init();
}

void CrustiLocker::loop()
{
  // If the button was pressed since the last loop
  if(button.wasPressed()) 
  {
    long unsigned int loopUntil = millis() + 1000*60*1; // Loop until 1 minute has passed

    while(millis() <= loopUntil) {
      led.setColor(255, 100, 0); 

      // If there is a new crusti transaction
      if(nordigen.newCrustiTransactionExists(network)) 
      {
        motor.start(100);
        
        while (!IR.wasPressed()) {} // Wait for IR scanner to trigger

        motor.stop();

        store.addCrustis(-1);
      };

      // Simulate doing work :P
      led.setColor(0, 0, 0);
      delay(1000);
      for (int i = 0; i < 5; i++)
      {
        led.setColor(255, 100, 0); 
        delay(1000);
        led.setColor(0, 0, 0);
        delay(1000);
      }
    }

    // Blink light red to show error
    for (int i = 0; i < 3; i++)
    {
      delay(150);
      led.setColor(255, 0, 0);
      delay(200);
      led.setColor(0, 0, 0);
    }

    // Clear button presses that happened during the transaction search
    button.wasPressed();
  }

  delay(1000);
}