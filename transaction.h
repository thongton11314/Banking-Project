#pragma once
#ifndef TRANSACTION
#define TRANSACTION
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//---------------------------------------------------------------------------
// Transaction class:  
//   -- Holds the information of deposit, withdraw, and move
//   -- Checks if transaction is possible/valid when reading from file
//
// Assumptions:
//   -- A transaction that would cause a balance to become
//      negative should not occur and is an error.
//   -- Transaction type:
//          D buy shares, i.e., deposit funds
//          W sell shares, i.e., withdraw funds
//          M move assets between funds / clients
//          H show the client history
//   -- Move is just a withdraw and deposit put together.

// Implementation:
//   -- The data of the transaction will be given by setData function.
//      Data will be assign by ifstream.
//   -- The set funtion use to set transaction in case of move transaction
//      It may be called from manager class.
//   -- It means that when the transaction type is performed: 
//      The deliver client has a history of transaction type move,
//      The reciever client will have a history of transaction type deposit.
//---------------------------------------------------------------------------

class Transaction {

    // display transaction information
    friend ostream& operator<<(ostream &, const Transaction&);

public:
    Transaction();                    // constructor
    ~Transaction();                   // deconstructor
    bool setData(ifstream&);          // fill transaction data from file
    void setDeliveredClientID(int);   // set deliver ID
    void setReceivedClientID(int);    // set receiver ID
    void setDeliveredAccID(int);      // set deliver account
    void setReceivedAccID(int);       // set receiver account
    void setTransType(char);          // set transaction type
    void setAmount(int);              // set transaction amount
    int getDeliveredClientID() const; // retrieve deliver ID
    int getReceivedClientID() const;  // retrieve receiver ID
    int getDeliveredAccID() const;    // retrieve deliver account
    int getReceivedAccID() const;     // retrieve receiver account
    char getTranType() const;         // retrieves transaction type
    int getAmount() const;            // retrieves amount of money
    void accDescription(int) const;   // account descrption

private:
    int deliveredClientID;            // deliver ID
    int receivedClientID;             // receiver ID
    int deliveredAccID;               // account of deliver
    int receivedAccID;                // account of reciever
    int amount;                       // amount of money
    char transType;                   // store as deposit, withdraw, move
};
#endif // !TRANSACTION