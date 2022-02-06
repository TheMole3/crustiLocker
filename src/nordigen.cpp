/*

  nordigen.h - Library for communication with nordigen

*/

#include "Arduino.h"
#include "Nordigen.h"

#include <regex>

#include "Store.h"

Nordigen::Nordigen()
{
    Store Storage;
    endUserId = Storage.getConfigValue("endUserId");
    access_token = Storage.getConfigValue("access_token");
    requisition_UUID = Storage.getConfigValue("requisition_UUID");
    account_UUID = Storage.getConfigValue("account_UUID");
    aspsp_id = Storage.getConfigValue("aspsp_id");
    
    endUserId.trim();
    access_token.trim();
    requisition_UUID.trim();
    account_UUID.trim();
    aspsp_id.trim();
    
}

bool Nordigen::newCrustiTransactionExists(Network network)
{
    bool status = false;
    if(WiFi.status()== WL_CONNECTED){
        String serverPath = apiURL + "/accounts/" + account_UUID + "/transactions/";
        
        String transactions = network.httpGETRequest(serverPath.c_str(), access_token);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, transactions);
        JsonObject obj = doc.as<JsonObject>();

        if(obj["statusCode"].as<int>() != 200) // If there was an error at nordigen
        {
            Serial.println("Error!\n" + transactions);
            // TODO - send error to pushbullet
        } 
        else 
        {
            // Loop thru transactions to serach for a new matching one
            for (int i = 0; i < obj["transactions"].size(); i++)
            {
                // If the transactions matches the criteria for amount and message
                if(obj["transactions"][i]["transactionAmount"]["amount"] == Store().getConfigValue("PRICE") && obj["transactions"][i]["remittanceInformationUnstructured"] == Store().getConfigValue("MESSAGEMATCH")) {
                    // Check if this transaction already has been dispensed
                }
            }     
        }
    }

    return status;
}


String Nordigen::getRequsitionLink(Network network) 
{
    String requsitionLink;
    if(WiFi.status()== WL_CONNECTED){
        String serverPath = apiURL + "/requisitions/" + requisition_UUID + "/links/";
         
        String requsition = network.httpPOSTRequest(serverPath.c_str(),"{\"aspsp_id\": \"" + aspsp_id + "\"}", access_token);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, requsition);
        JsonObject obj = doc.as<JsonObject>();

        if(obj["statusCode"].as<int>() != 200) // If there was an error at nordigen
        {
            Serial.println("Error!\n" + requsition);
            // TODO - send error to pushbullet
        } 
        else 
        {
            requsitionLink = obj["initiate"].as<String>();;
        }
    }
    return requsitionLink;
};