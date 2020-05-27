#pragma once
#ifndef MANAGER
#define MANAGER
#include <iostream>
#include <fstream>
#include "bst.h"
#include "queue.h"

using namespace std;

class Manager {

public:
    Manager() {};                           // constructor
    ~Manager() {};                          // destructor 
    void buildClients(ifstream &);          // add clients from file
    void buildTransactions(ifstream &);     // add transaction commands file
    void processTransactions();             // process all transactions
    void report();                          // get report of the day

private:
    BSTree clientContainer;                 // hold a client container
    Queue transactionContainer;             // hold all transaction container
    Queue invalidTransactionContainer;      // hold invalid transaction
    void moveHelper(Transaction*);          // perform move
    void depositHelper(Transaction*);       // perform deposit
    void withdrawHelper(Transaction*);      // perform withdraw
    void invalidTransactions();             // show invalid transactions
    void clientSummary();                   // show accounts summary
    void clientsReport();                   // show all client infor and account
};

#endif // !MANAGER

