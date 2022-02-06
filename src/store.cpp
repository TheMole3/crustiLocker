/*

  store.h - Library for storing and reading presistent data

*/

#include "Arduino.h"
#include "store.h"

#include <string>

bool store::checkTransaction(String id) 
{
  bool found = false;

  LittleFS.begin();

  File file = LittleFS.open(transactionFile, "a+");
  
  while (file.available()) 
  {
    String foundId = file.readStringUntil('\n');

    if (foundId.toInt() == id.toInt()) 
    {
      found = true;
      break;
    } 
  }

  if(!found) {
    file.println(id);
  }

  LittleFS.end();

  return found;
}



int store::getCrustis() 
{
  int crustisLeft = 0;

  LittleFS.begin();

  File file = LittleFS.open(crustiFile, "a+");
  
  while (file.available()) 
  {
    String amount = file.readStringUntil('\n');

    crustisLeft = amount.toInt();
  }

  LittleFS.end();

  return crustisLeft;
};

int store::setCrustis(int amount) 
{
  LittleFS.begin();

  File file = LittleFS.open(crustiFile, "w");

  file.print(amount);

  LittleFS.end();

  return amount;
};

int store::addCrustis(int amount) 
{
  int newAmount = getCrustis() + amount;

  LittleFS.begin();

  File file = LittleFS.open(crustiFile, "w");

  file.print(newAmount);

  LittleFS.end();

  return newAmount;
};


String store::getConfigValue(String key) 
{
  String value;

  LittleFS.begin();

  File file = LittleFS.open(configFile, "r");
  
  while (file.available()) 
  {
    String foundKey = file.readStringUntil('=');
    String foundValue = file.readStringUntil('\n');

    if (foundKey == key) 
    {
      value = foundValue;
      break;
    }
  }

  LittleFS.end();

  return value;
}

void store::setConfigValue(String key, String val) 
{
  String config = "";

  LittleFS.begin();

  File file = LittleFS.open(configFile, "a+");
  
  while (file.available()) 
  {
    String foundKey = file.readStringUntil('=');
    String foundValue = file.readStringUntil('\n');
    
    if(foundKey == key) 
    {
      foundValue = val;
    }
    
    config += foundKey + "=" + foundValue + "\n";
  }

  delay(1);
  file.close();

  File fileWrite = LittleFS.open(configFile, "w");

  fileWrite.print(config);

  delay(1);
  file.close();

  LittleFS.end();
}