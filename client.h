#pragma once
#ifndef CLIENT
#define CLIENT
#include <fstream>
#include <string>
#include <iomanip>
#include "loseAccount.h"
#include "queue.h"

using namespace std;

const int MINID = 1;        // smallest id
const int MAXID = 9999;     // highest id
const int MAXACCOUNT = 10;  // maximum number of accounts
const int CONVERTED = 10; // convert account id 5 digit into 1 digit

class Client {
    friend ostream& operator<<(ostream &, const Client&);
public:

    Client();                   
    ~Client();                   
    Client(const Client&);      
    void setId(int);             
    bool setData(ifstream&);     
    bool deposit(int, int);        
    bool withdraw(int, int);        
    int getId() const;              
    int getStartBalance(int) const; 
    int getFinalBalance(int) const;
    void addHistory(Transaction*);
    Client& operator=(const Client&);
    bool operator<(const Client&) const;
    bool operator<=(const Client&) const;
    bool operator>(const Client&) const;
    bool operator>=(const Client&) const;
    bool operator==(const Client&) const;
    bool operator!=(const Client&) const;

private:
    string firstName;               
    string lastName;                  
    int clientID;                     
    LOSEAccount loseAccount[MAXACCOUNT];
    Queue historyContainer;          
};
#endif // !CLIENT
