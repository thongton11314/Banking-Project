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
//   -- If transaction is type of move:
//          accountIDOne will hold id of taken account
//          accountIDTwo will hold id of recieve account
//
//---------------------------------------------------------------------------

class Transaction {

    // display transaction information
    friend ostream& operator<<(ostream &, const Transaction&);

public:

    // default constructor
    Transaction();
    Transaction(const Transaction&);      // copy constructor
    bool setData(ifstream&);              // fill transaction data from file
    bool deposit(int, double);            // deposits amount into account
    bool withdraw(int, double);           // withdraws amount from account
    void move(int, double, int);          // transfers amount to new account
    int getClientIDOne() const;
    int getClientIDTwo() const;
    int getAccIDOne() const;              // deliver account
    int getAccIDTwo() const;              // receiver account
    char getTranType() const;             // retrives transaction type
    double getAmount() const;             // retrieves amount of money

    // copy operator
    Transaction& operator=(const Transaction&);

    // comparison operators 
    bool operator<(const Transaction&) const;
    bool operator<=(const Transaction&) const;
    bool operator>(const Transaction&) const;
    bool operator>=(const Transaction&) const;
    bool operator==(const Transaction&) const;
    bool operator!=(const Transaction&) const;

private:
    int clientIDOne;
    int clientIDTwo;
    int AccIDOne;             // use for account id
    int AccIDTwo;              // use for account id incase for move
    double amount;                  // amount of money
    char transType;                 // store as deposit, withdraw, move
};
#endif // !_TRANSACTION_

