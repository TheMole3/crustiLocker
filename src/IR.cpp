/*

  IR.h - Library for detecting button presses

*/

#include "Arduino.h"
#include "IR.h"

IR::IR(int pin, int enablePin)
{
    pinMode(pin, INPUT_PULLUP);
    pinMode(enablePin, OUTPUT);

    objectDetect = false;

    _pin = pin;
    _enablePin = enablePin;
};

bool IR::wasPressed() 
{
    bool status = objectDetect;
    this->objectDetect = false;
    return status;
}

void IR::loop()
{
    digitalWrite( _enablePin, HIGH);    // Enable the internal 38kHz signal.
    delayMicroseconds( 210);            // Wait 210µs (8 pulses of 38kHz).
    if( digitalRead( _pin))             // If detector Output is HIGH,
    {
        objectDetect = false;           // then no object was detected;
    }
    else                                // but if the Output is LOW,
    {
        delayMicroseconds( 395);        // wait for another 15 pulses.
        if( digitalRead( _pin))         // If the Output is now HIGH,
        {                               // then first Read was noise
            objectDetect = false;       // and no object was detected;
        }
        else                            // but if the Output is still LOW,
        {
            objectDetect = true;        // then an object was truly detected.
        }
    }
    digitalWrite( _enablePin, LOW);     // Disable the internal 38kHz signal.
    Serial.println(objectDetect);
}