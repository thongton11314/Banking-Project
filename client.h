#pragma once
#ifndef CLIENT
#define CLIENT
#include <fstream>
#include <string>
#include <iomanip>
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
//   -- Client ID is limited, cannot bellow 0 and exceed 9999.
//   -- The account of client can never be negative.
//
//---------------------------------------------------------------------------

const int MINID = 1;        // smallest id
const int MAXID = 9999;     // highest id
const int MAXACCOUNT = 10;  // maximum number of accounts
const int CONVERTED = 10; // convert account id 5 digit into 1 digit

class Client {

    // display client information
    friend ostream& operator<<(ostream &, const Client&);

public:

    Client();                       // constructor
    ~Client();                      // deconstuctor  
    Client(const Client&);          // copy constructor
    void setId(int);                // set account id
    bool setData(ifstream&);        // fill object with data from f
    bool deposit(int, int);         // deposit LOSE account
    bool withdraw(int, int);        // remove LOSE account
    int getId() const;              // get account id
    int getStartBalance(int) const; // get start balance
    int getFinalBalance(int) const; // get final balance
    void addHistory(Transaction*);// add transaction history

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
    string firstName;                   // client first name
    string lastName;                    // client last name
    int clientID;                       // client ID
    LOSEAccount loseAccount[MAXACCOUNT];// holding ten Lot of saving account
    Queue historyContainer;             // hold client transaction history
};
#endif // !CLIENT