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
    Manager() {};   
    ~Manager() {};                      
    void buildClients(ifstream &);       
    void buildTransactions(ifstream &);   
    void processTransactions();   
    void report();                    

private:
    BSTree clientContainer;               
    Queue transactionContainer;           
    Queue invalidTransactionContainer;    
    void moveHelper(Transaction*);      
    void depositHelper(Transaction*);    
    void withdrawHelper(Transaction*);   
    void invalidTransactions();          
    void clientSummary();              
    void clientsReport();  
};
#endif // !MANAGER
