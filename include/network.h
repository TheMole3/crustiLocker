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

#include "Pushbullet.h"         // Include Pushbullet

class Network 
{
  public:
    void init(Pushbullet &pushbullet);

    String httpGETRequest(const char* serverName, String access_token="");
    String httpPOSTRequest(const char* serverName, String body, String access_token="");

    // Pushbullet ref
    Pushbullet &pushbullet;

  private:
    Store store;
    const char* ssid        = store.getConfigValue("networkSSID").c_str(); // The SSID (name) of the Wi-Fi network you want to connect to
    const char* password    = store.getConfigValue("networkPASS").c_str(); // The password of the Wi-Fi network
};


#endif