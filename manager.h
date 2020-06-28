#pragma once
#ifndef MANAGER
#define MANAGER
#include <iostream>
#include <fstream>
#include "bst.h"
#include "queue.h"

//---------------------------------------------------------------------------
// Manager class:
//  -- Connect other classes to work together.
//  -- Have a binary search tree of client.
//  -- Have a queue of all transaction.
//  -- Have other queues to handle errors.
//  -- Get data from file that has clients, transactions then put them in
//      containers.
// 
// Assumption:
//  -- All data that is retrieved from file should be correctly formatted
//  -- When individual transactions are performed, 
//      won't display a message for a correctly performed
//      transaction. Do display error messages for incorrect transactions.
//  -- Transaction type:
//          D buy shares, i.e., deposit funds.
//          W sell shares, i.e., withdraw funds.
//          M move assets between funds / clients.
//          H show client history.
//
// Implementation:
//  -- Use Binary Search Tree to store all clients.
//  -- Use Queue to store all transactions.
//  -- Use Three Queues to store different type of error
//       - errorTransaction: will store transaction type are not D,W,M.
//       - errorInsufficientFUnd : will store insufficient transaction.
//       - errorUnknownClient: will store bad client information.
//
//---------------------------------------------------------------------------

using namespace std;

class Manager {

public:
    Manager();                          // constructor
    ~Manager();                         // destructor 
    void buildClients(ifstream &);      // add clients from file
    void buildTransactions(ifstream &); // add transaction commands file
    void processTransactions();         // process all transactions
    void report();                      // get report of the day

private:
    BSTree clientContainer;             // hold a client container
    Queue transactionContainer;         // hold all transaction container

    // hold different type of error
    Queue errorTransactions;            // hold error transactions
    Queue errorInsufficientFunds;       // hold bad amount of transactions
    Queue errorUnknownClients;          // hold unknown clients
    void move(Transaction*);            // perform move transaction
    void deposit(Transaction*);         // perform deposit transaction
    void withdraw(Transaction*);        // perform withdrawtransaction
    void history(Transaction*);         // show client history
    void invalidTransactions();         // show invalid transactions
};
#endif // !MANAGER