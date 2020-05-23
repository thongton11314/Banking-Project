#pragma once
#ifndef CLIENT
#define CLIENT
#include <fstream>
#include "loseAccount.h"
#include "queue.h"

using namespace std;

//---------------------------------------------------------------------------
// Client class:  
//   -- holds the primary information of the client
//   -- calls for transactions
//   -- displays client's transaction history
//
// Implementation and assumptions:
//   -- Maximum account of client has is 10 accounts
//   -- listLOSE index present for each section bellow
//      0: Money Market         5: Capital Value Fund
//      1: Prime Money Market   6: Growth Equity Fund
//      2: Long-Term Bond       7: Growth Index Fund
//      3: Short-Term Bond      8: Value Fund
//      4: 500 Index Fund       9: Value Stock Index
//
//   -- Client ID is limited, cannot exceed 9999
//
//---------------------------------------------------------------------------

const int MAXID = 9999;
const int MAXACCOUNT = 10;
const int MAXLENGTH = 25;

class Client {

    // display client information
    friend ostream& operator<<(ostream &, const Client&);

public:

    // default constructor
    Client(char[MAXLENGTH] = 0, char[MAXLENGTH] = 0, int = 0);
    ~Client();                           // deconstuctor      
    Client(const Client&);               // copy constructor
    void setClientId(int);               // set account id
    bool setData(ifstream&);             // fill object with data from f
    void deposit(int, double);           // deposit accounts
    void withdraw(int, double);          // withdraw accounts
    int getClientId() const;             // get account id
    void addHistory(const Transaction&); // add transaction history
    void displayAllHistory() const;      // display all transaction
    
    // copy operator
    Client& operator=(const Client&);

    // comparison operators 
    bool operator<(const Client&) const;
    bool operator<=(const Client&) const;
    bool operator>(const Client&) const;
    bool operator>=(const Client&) const;
    bool operator==(const Client&) const;
    bool operator!=(const Client&) const;

private:
    char firstName[MAXLENGTH];           // client first name
    char lastName[MAXLENGTH];            // client last name
    int clientID;                        // client ID
    LOSEAccount loseAccount[10];         // holding ten Lot of saving account
    Queue historyContainer;              // hold client transaction history
};
#endif // !CLIENT

