#pragma once
#ifndef _TRANSACTION_
#define _TRANSACTION_
#include <fstream>

using namespace std;

//---------------------------------------------------------------------------
// Transaction class:  
//   -- handles deposit, withdraw, and move
//   -- checks to see if transaction is possible/valid
//
// Implementation and assumptions:
//   -- A transaction that would cause a balance to become
//      negative should not occur and is an error.
//   -- If withdrawing from a money market account with insufficient
//      funds, but it can be covered with funds from another money market.
//   -- The desired amount(only the partial amount needed to cover
//      the withdrawal) is moved to that money market account.
//      Bond accounts are handled similarly.
//      No other types of accounts are handled in this manner.
//   -- When individual transactions are performed, 
//      do not display a message for a correctly performed
//      transaction.Do display error messages for incorrect transactions.
//   -- Transaction type:
//          D buy shares, i.e., deposit funds
//          W sell shares, i.e., withdraw funds
//          M move assets between funds / clients
//   -- The data of the transaction will be given by setData function
//      , which there has no set data. Datas will be assign by ifstream
//
//---------------------------------------------------------------------------

class Transaction {

    // display transaction information
    friend ostream& operator<<(ostream &, const Transaction&);

public:
    Transaction();                    // constructor
    ~Transaction();                   // deconstructor
    bool setData(ifstream&);          // fill transaction data from file
    int getDeliveredClientID() const; // retrieve deliver ID
    int getReceivedClientID() const;  // retrieve receiver ID
    int getDeliveredAccID() const;    // retrieve deliver account
    int getReceivedAccID() const;     // retrieve receiver account
    char getTranType() const;         // retrieves transaction type
    int getAmount() const;            // retrieves amount of money

private:
    int deliveredClientID;            // deliver ID
    int receivedClientID;             // receiver ID
    int deliveredAccID;               // account of deliver
    int receivedAccID;                // account of reciever
    int amount;                       // amount of money
    char transType;                   // store as deposit, withdraw, move
};
#endif // !_TRANSACTION_
