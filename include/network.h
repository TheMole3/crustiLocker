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
#include "Store.h"              // Include Storage library

class Network 
{
  public:
    Network();
    void init(Pushbullet pushbullet);

    String httpGETRequest(const char* serverName, String access_token="");
    String httpPOSTRequest(const char* serverName, String body, String access_token="");


  private:
    Store store;
    
    // Pushbullet ref
    Pushbullet pushbullet;

    String ssid        = store.getConfigValue("networkSSID"); // The SSID (name) of the Wi-Fi network you want to connect to
    String password    = store.getConfigValue("networkPASS"); // The password of the Wi-Fi network
};


#endif