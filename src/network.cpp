/*

  network.h - Library for using ESP network features

*/

#include "Arduino.h"
#include "Network.h"

Network::Network(){}

void Network::init(Pushbullet pushbullet)
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

    // Save pushbullet reference
    this->pushbullet = pushbullet;
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
    if(access_token) http.addHeader("Authorization", "Bearer " + access_token, true);
    
    http.addHeader("Content-Length", "0");
    
    // Send HTTP GET request
    int httpResponseCode = http.GET();
    
    String payload = "{}"; 
    
    if (httpResponseCode == 200) 
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else 
    {
        Serial.print("HTTP Error code: ");
        Serial.println(httpResponseCode);

        pushbullet.push("Network error", 
        "GET request\n"
        "Code: " + String(httpResponseCode) + "\n"
        "URL: " + String(serverName) + "\n"
        );
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
    if(access_token) http.addHeader("Authorization", "Bearer " + access_token, true);
    
    http.addHeader("Content-Type", "application/json");

    // Send HTTP POST request
    int httpResponseCode = http.POST(body);
    
    String payload = "{}"; 
    
    if (httpResponseCode == 200) 
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else 
    {
        Serial.print("HTTP Error code: ");
        Serial.println(httpResponseCode);

        pushbullet.push("Network error", 
        "POST request\n"
        "Code: " + String(httpResponseCode) + "\n"
        "URL: " + String(serverName) + "\n"
        "Body: " + String(body) + "\n"
        );
    }
    // Free resources
    http.end();

    return payload;
}