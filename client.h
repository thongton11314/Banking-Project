#ifndef CLIENT
#define CLIENT
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "loseAccount.h"
#include "queue.h"

using namespace std;

//---------------------------------------------------------------------------
// Client class:  
//   -- holds the primary information of the client
//      - client's last name, first name, ID.
//   -- holds client's transaction history
//      - client's transaction will be store in Queue.
//
// Assumptions:
//   -- Maximum account of client has is 10 accounts
//      - listLOSE index present for each section bellow
//        0: Money Market         5: Capital Value Fund
//        1: Prime Money Market   6: Growth Equity Fund
//        2: Long-Term Bond       7: Growth Index Fund
//        3: Short-Term Bond      8: Value Fund
//        4: 500 Index Fund       9: Value Stock Index
//
//   -- Rule of overwithdraw
//      - If overwithdraw from account 0 or 1, they can be cover each other.
//      - If overwithdraw form account 2 or 3, they can be cover each other.
//      - Other overwithdraw can not be covered by any other account, 
//        only 0-1, 2-3 can cover each other. 
//
//   -- Client ID is limited, cannot go below 0 and exceed 9999.
//   -- The account of client can never be negative.
//
// Implementation:
//   -- comparison operators will compare client ID.
//   -- setData function will help read client's data from the file
//   -- constants are used to cover ID ranges and number of accounts
//---------------------------------------------------------------------------

const int MINID = 1;                    // smallest id
const int MAXID = 9999;                 // highest id
const int MAXACCOUNT = 10;              // maximum number of accounts
const int CONVERTED = 10;               // use to get the last digit

class Client {

    // display client information
    friend ostream& operator<<(ostream &, const Client&);

public:

    Client();                           // constructor
    ~Client();                          // deconstuctor  
    void setId(int);                    // set account id
    bool setData(ifstream&);            // fill object with data from file
    bool deposit(int, int);             // deposit LOSE account
    bool withdraw(int, int);            // remove LOSE account
    string getLastName() const;         // get client last name
    string getFirstName() const;        // get client first name
    int getId() const;                  // get account ID
    int getInitialBalance(int) const;   // get start balance
    int getFinalBalance(int) const;     // get final balance
    bool addHistory(Transaction*);      // add transaction history
    bool isEmptyHistory() const;        // check for client transactions
    void displayHistory();              // display history

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
    LOSEAccount loseAccount[MAXACCOUNT];// holds the ten LOSE accounts
    Queue historyContainer;             // holds client transaction history
};
#endif // !CLIENT