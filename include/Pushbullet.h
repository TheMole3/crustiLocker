/*

  Pushbullet.h - Library for pushbullet messaging

*/

#ifndef Pushbullet_h
#define Pushbullet_h

#include "Arduino.h"

#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266HTTPClient.h>  // Include the request library

#include "Store.h"

class Pushbullet
{
  public:
    Pushbullet();

    void push(String title, String message) ;

  private:
    Store storage;
    String _token = storage.getConfigValue("PUSHBULLET_TOKEN");
    String _channel = storage.getConfigValue("PUSHBULLET_CHANNEL");
};


#endif