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
    Store Storage;

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
        } 
        else
        {
            // Loop thru transactions to serach for a new matching one
            for (int i = 0; i < obj["transactions"].size(); i++)
            {
                // If the transactions matches the criteria for amount and message
                if(obj["transactions"][i]["transactionAmount"]["amount"] == Store().getConfigValue("PRICE") && obj["transactions"][i]["remittanceInformationStructured"] == "swish mottagen") 
                {
                    // Check that the transaction hasn't already been dispensed
                    if(Storage.checkTransaction(obj["transactions"][i]["transactionId"]))
                    {
                        status = true;
                        break;
                    }
                }
            }
        }
    }

    return status;
}


String Nordigen::getRequsitionLink(Network network) 
{
    String requsitionLink;
    if(WiFi.status()== WL_CONNECTED)
    {
        String serverPath = apiURL + "/requisitions/" + requisition_UUID + "/links/";
         
        String requsition = network.httpPOSTRequest(serverPath.c_str(),"{\"aspsp_id\": \"" + aspsp_id + "\"}", access_token);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, requsition);
        JsonObject obj = doc.as<JsonObject>();

        if(obj["statusCode"].as<int>() != 200) // If there was an error at nordigen
        {
            Serial.println("Error!\n" + requsition);

            pushbullet.push("Nordigen error", 
            "Get requsition link\n"
            "Code: " + String(obj["statusCode"].as<int>() ) + "\n"
            "Requsition: " + String(requsition)
            );
        } 
        else 
        {
            requsitionLink = obj["initiate"].as<String>();;
        }
    }
    return requsitionLink;
};

String Nordigen::createRequisitionLink(Network network)
{
    // Make sure that we have WIFI
    if(WiFi.status()== WL_CONNECTED) 
    {

        // Delete the old requsition
        String deleteRequstitionPath = apiURL + "/requisitions/" + requisition_UUID;
        String deletedRequstion = network.httpDELETERequest(deleteRequstitionPath.c_str(), access_token);

        // Create a new requsition
        String newRequsitionPath = apiURL + "/requsitions/";
        String newRequsition = network.httpPOSTRequest(newRequsitionPath.c_str("""
        {  
            \"redirect\": \"https://thumbs.dreamstime.com/b/done-text-green-grungy-vintage-rectangle-stamp-done-text-green-grungy-vintage-stamp-214435444.jpg\",
            \"institution_id\": \"
            \"reference\": \"crustiLocker\",  
            \"enduser_id\": \"crustiLocker\",  
            \"agreements\": [] 
        }
        """), access_token)

        // Convert responce to JSON
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, newRequsition);
        JsonObject obj = doc.as<JsonObject>();

        if(obj["statusCode"].as<int>() != 200) // If there was an error at nordigen
        {
            Serial.println("Error!\n" + newRequsition);

            pushbullet.push("Nordigen error", 
            "Create requsition link\n"
            "Code: " + String(obj["statusCode"].as<int>() ) + "\n"
            "Requsition: " + String(newRequsition)
            );
        } 
        else 
        {
            // Save the requsition id
            String id = obj["id"].as<String>();
            Store.setConfigValue("requisition_UUID", id);
        }
    }
}

