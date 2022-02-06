/*

  network.h - Library for using ESP network features

*/

#ifndef network_h
#define network_h

#include "Arduino.h"

#include <string>

#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266HTTPClient.h>  // Include the request library
#include <ArduinoJson.h>        // Include json library

class Network 
{
  public:
    void init();

    String httpGETRequest(const char* serverName, String access_token="");
    String httpPOSTRequest(const char* serverName, String body, String access_token="");

  private:
    const char* ssid        = "CrustiLocker";         // The SSID (name) of the Wi-Fi network you want to connect to
    const char* password    = "CrustiLocker2022";     // The password of the Wi-Fi network
};


#endif