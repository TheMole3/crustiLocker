/*

  store.h - Library for storing and reading presistent data

*/

#include "Arduino.h"
#include "store.h"

#include <string>

bool Store::checkTransaction(String id) 
{
  bool found = false;

  LittleFS.begin();

  File file = LittleFS.open(transactionFile, "a+");
  
  while (file.available()) 
  {
    String foundId = file.readString() + "-";
    Serial.println(foundId);

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



int Store::getCrustis() 
{
  int crustisLeft = 0;

  LittleFS.begin();

  File file = LittleFS.open(crustiFile, "r");

  String amount = file.readString();
  amount.trim();
  Serial.println(amount);
  crustisLeft = amount.toInt();
  Serial.println(crustisLeft);

  LittleFS.end();

  return crustisLeft;
};

int Store::setCrustis(int amount) 
{
  LittleFS.begin();

  File file = LittleFS.open(crustiFile, "w");

  file.println(amount);

  LittleFS.end();

  return amount;
};

int Store::addCrustis(int amount) 
{
  int newAmount = getCrustis() + amount;

  LittleFS.begin();

  File file = LittleFS.open(crustiFile, "w");

  file.println(newAmount);

  LittleFS.end();

  return newAmount;
};


String Store::getConfigValue(String key) 
{
  String value;

  LittleFS.begin();

  File file = LittleFS.open(configFile, "r");
  if(!file) Serial.println("File failed to open, get config value");
  
  while(file.available())
  {
    String foundKey = file.readStringUntil('=');
    String foundValue = file.readStringUntil('\n');

    if (foundKey == key) 
    {
      value = foundValue;
      value.trim();
      break;
    }
  }

  LittleFS.end();

  return value;
}

void Store::setConfigValue(String key, String val) 
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