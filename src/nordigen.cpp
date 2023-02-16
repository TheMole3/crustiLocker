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
    // Initialise storeage
    Store storage;

    bool status = false;
    if(WiFi.status()== WL_CONNECTED){ // If wifi connected
        String serverPath = apiURL + "/transactions";
        
        // get bank transactions
        String transactions = network.httpGETRequest(serverPath.c_str(), token);

        // Create a JSON doc
        DynamicJsonDocument doc(2048);
        deserializeJson(doc, transactions);
        JsonArrayConst obj = doc.as<JsonArray>();

        // Check for valid unused transaction
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