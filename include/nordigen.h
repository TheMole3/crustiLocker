/*

  nordigen.h - Library for communication with nordigen

*/

#ifndef Nordigen_h
#define Nordigen_h

#include "Arduino.h"

#include "Network.h"

class Nordigen 
{
  public:
    Nordigen();

    // Check if a new transaction for a crusti has appeared in the bank
    bool newCrustiTransactionExists(Network network);

    // Get a requsitionLink to update nordigen, returns null if no requsition could be made
    String getRequsitionLink(Network network);

    // Generate a new requsition link
    String Nordigen::createRequisitionLink(Network network);

  private:
    String apiURL   = "https://proxy.melo.se/nordigen/api";

    String endUserId; // Nordigen endUserId
    String access_token; // The nordigen access token
    String requisition_UUID; // The UUID of the requisition
    String account_UUID; // The UUID of the bank account to check for transactions
    String aspsp_id; // Sandbox
};


#endif