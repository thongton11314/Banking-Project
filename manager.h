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
    Manager() {};                       // constructor
    ~Manager() {};                      // destructor 
    void buildClients(ifstream &);      // add clients from file
    void buildTransactions(ifstream &); // add transaction commands file
    void processTransactions();         // process all transactions
    void displayReport() const;         // display all of transactions

private:
    BSTree clientContainer;             // hold a client container
    Queue transactionContainer;         // hold a transaction container
};
#endif // !MANAGER

