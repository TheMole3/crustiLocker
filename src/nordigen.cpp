/*

  nordigen.h - Library for communication with nordigen

*/

#include "Arduino.h"
#include "Nordigen.h"

#include <regex>

#include "Store.h"

Nordigen::Nordigen()
{        
    token.trim();
}

bool Nordigen::newCrustiTransactionExists(Network network)
{
    Store storage;

    bool status = false;
    if(WiFi.status()== WL_CONNECTED){
        String serverPath = apiURL + "/transactions";
        
        Serial.println(token);
        String transactions = network.httpGETRequest(serverPath.c_str(), token);

        DynamicJsonDocument doc(2048);
        deserializeJson(doc, transactions);
        JsonArrayConst obj = doc.as<JsonArray>();

        for (JsonVariantConst value : obj) {
            Serial.println(value.as<String>());
            Serial.println(value["transactionId"].as<String>());
            if(storage.checkTransaction(value["transactionId"].as<String>()))
            {
                status = true;
                break;
            }
        }
    }

    return status;
}