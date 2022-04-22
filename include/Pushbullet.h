/*

  Pushbullet.h - Library for pushbullet messaging

*/

#ifndef Pushbullet_h
#define Pushbullet_h

#include "Arduino.h"

#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266HTTPClient.h>  // Include the request library

class Pushbullet
{
  public:
    Pushbullet(String token, String channel);
    ~Pushbullet();

    void push(String title, String message) ;

  private:
    const char* _token;
    const char* _channel;
};


#endif