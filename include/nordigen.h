/*

  nordigen.h - Library for communication with nordigen

*/

#ifndef Nordigen_h
#define Nordigen_h

#include "Arduino.h"

#include "Network.h"
#include <ArduinoJson.h>        // Include json library

class Nordigen 
{
  public:
    Nordigen();

    // Check if a new transaction for a crusti has appeared in the bank
    bool newCrustiTransactionExists(Network network);

  private:
    const String apiURL   = "https://crusti.melo.se";

    Store storage;
    String token = storage.getConfigValue("TOKEN"); // crusti.melo.se Access token
};

#endif