/*

  Pushbullet.h - Library for pushbullet messaging

*/

#include "Arduino.h"
#include "Pushbullet.h"

Pushbullet::Pushbullet() {};

void Pushbullet::push(String title, String message) 
{
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;

    // Your IP address with path or Domain name with URL path 
    http.begin(client, "https://api.pushbullet.com/v2/pushes");

    // Add auth header
    http.addHeader("Access-Token", _token, true);
    
    http.addHeader("Content-Type", "application/json");

    String json = "{\"type\":\"note\", \"title\":\"" + title + "\", \"body\":\"" + message + "\", \"channel_tag\":\""+ _channel + "\"}";

    // Send HTTP POST request
    int httpResponseCode = http.POST(json);
    Serial.println(httpResponseCode);
    http.end();
};