/*

  nordigen.h - Library for communication with nordigen

*/

#ifndef nordigen_h
#define nordigen_h

#include "Arduino.h"

#include "network.h"

class nordigen 
{
  public:
    nordigen();

    // Check if a new transaction for a crusti has appeared in the bank
    bool newCrustiTransactionExists(network Internet);

    // Get a requsitionLink to update nordigen, returns null if no requsition could be made
    String getRequsitionLink(network Internet);

  private:
    String apiURL   = "https://proxy.melo.se/nordigen/api";

    String endUserId; // Nordigen endUserId
    String access_token; // The nordigen access token
    String requisition_UUID; // The UUID of the requisition
    String account_UUID; // The UUID of the bank account to check for transactions
    String aspsp_id; // Sandbox
    //String aspsp_id           = "SWEDBANK_SWEDSESS"; // Swedbank
};


#endif