/*

  network.h - Library for using ESP network features

*/

#include "Arduino.h"
#include "Network.h"


void Network::init()
{
    // Setting ESP into STATION mode only (no AP mode or dual mode)
    wifi_set_opmode(STATION_MODE);
    
    WiFi.begin(ssid, password);             // Connect to the network
    Serial.print("\n\nConnecting to ");
    Serial.println(ssid);

    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        delay(1000);
        Serial.print('.');
    }

    Serial.println('\n');
    Serial.println("Connection established!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
    Serial.print("\n");
};


String Network::httpGETRequest(const char* serverName, String access_token) 
{
    Serial.println("GET " + String(serverName));

    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
        
    // Your IP address with path or Domain name with URL path 
    http.begin(client, serverName);

    // Add auth header
    if(access_token) http.addHeader("Authorization", "Token " + access_token, true);
    
    // Send HTTP POST request
    int httpResponseCode = http.GET();
    
    String payload = "{}"; 
    
    if (httpResponseCode>0) 
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else 
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);

        // TODO send error to pushbullet
    }
    // Free resources
    http.end();

    return payload;
}

String Network::httpPOSTRequest(const char* serverName, String body, String access_token) 
{
    Serial.println("POST " + String(serverName));

    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;

    // Your IP address with path or Domain name with URL path 
    http.begin(client, serverName);

    // Add auth header
    if(access_token) http.addHeader("Authorization", "Token " + access_token, true);
    
    http.addHeader("Content-Type", "application/json");

    // Send HTTP POST request
    int httpResponseCode = http.POST(body);
    
    String payload = "{}"; 
    
    if (httpResponseCode>0) 
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else 
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);

        // TODO send error to pushbullet
    }
    // Free resources
    http.end();

    return payload;
}