/*

  store.h - Library for storing and reading presistent data

*/

#ifndef store_h
#define store_h

#include <vector>

#include "Arduino.h"
#include "LittleFS.h" // LittleFS is declared

class Store 
{
  public:
    // Check if a transaction ID has already been dispensed, if it hasn't it will save the supplied ID to storage
    bool checkTransaction(String id);

    int getCrustis();
    int setCrustis(int amount);
    int addCrustis(int amount);

    String getConfigValue(String key);
    void setConfigValue(String key, String val);

  private:
    String configFile       = "config";
    String transactionFile  = "transactions";
    String crustiFile       = "cruistis";
};


#endif