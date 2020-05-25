#include <iostream>
#include "manager.h"

// build client container
void Manager::buildClients(ifstream & infile)
{
    Client* ptr;
    bool successfulRead;                             // read good data
    bool success;                                    // successfully insert
    for (;;) {
        ptr = new Client;

        // must have setData
        successfulRead = ptr->setData(infile);       // fill the Client object
        if (infile.eof()) {
            delete ptr;
            break;
        }

        // insert good data into the list, otherwise ignore it
        if (successfulRead) {
            success = clientContainer.insert(ptr);
        }
        else {
            delete ptr;
        }
        if (!success) break;
    }
}

// buil client transaction
void Manager::buildTransactions(ifstream & infile)
{
    Transaction* ptr;
    bool successfulRead;                             // read good data
    bool success;                                    // successfully insert
    for (;;) {
        ptr = new Transaction;

        // must have setData
        successfulRead = ptr->setData(infile);       // fill the Transaction object
        if (infile.eof()) {
            delete ptr;
            break;
        }

        // insert good data into the list, otherwise ignore it
        if (successfulRead) {
            success = transactionContainer.enqueue(ptr);
        }
        else {
            delete ptr;
        }
        if (!success) break;
    }
}

// process transactions from transaction container
void Manager::processTransactions()
{
    // early exist
    if (transactionContainer.isEmpty())
        return;

    // pointer that used for holding data
    Transaction* ptrTransaction;

    // get data from container
    while (transactionContainer.dequeue(ptrTransaction)) {

        switch (ptrTransaction->getTranType()) {
            
            // transaction type move
            case 'M':
                moveHelper(ptrTransaction);

            // transaction type deposit
            case 'D':
                depositHelper(ptrTransaction);
            
            // transaction type withdraw
            case 'W':
                withdrawHelper(ptrTransaction);
            
            // error transaction
            default:
                invalidTransactionContainer.enqueue(ptrTransaction);
        }
    }
    
    // delete pointer
    delete ptrTransaction;
    ptrTransaction = nullptr;
}

// this function will be called in processTransactions function
void Manager::moveHelper(Transaction *ptrTran) {

    // transaction type of move
    if (ptrTran->getTranType() == 'M') {

        // temporary pointer point to transaction data
        Client* ptrClientOne;
        Client* ptrClientTwo;

        // temporary target to check
        Client delTarget;
        Client recTarget;

        // initialize temporary target
        delTarget.setId(ptrTran->getDeliveredClientID());
        recTarget.setId(ptrTran->getReceivedClientID());

        // check deliver target
        bool checkOne = clientContainer.retrieve(delTarget, ptrClientOne);

        // check receiver target
        bool checkTwo = clientContainer.retrieve(recTarget, ptrClientTwo);

        // perfrom transaction
        if (checkOne && checkTwo) {

            // withdraw from deliver account
            ptrClientOne->withdraw(ptrTran->getDeliveredAccID()
                , ptrTran->getAmount());

            // deposit to receiver account
            ptrClientTwo->deposit(ptrTran->getReceivedAccID()
                , ptrTran->getAmount());

            // add history transaction into deliver account
            //ptrClientOne->addHistory(*ptrTran);
        }

        // error tracsaction
        else {
            invalidTransactionContainer.enqueue(ptrTran);
        }

        // delete pointers
        delete ptrClientOne;
        delete ptrClientTwo;
        ptrClientOne = ptrClientTwo = nullptr;
    }
}

// this function will be called in processTransactions function
void Manager::depositHelper(Transaction *ptrTran) {

    // pointer that hold a client data
    Client* ptrClient;

    // temporary target to check
    Client target;

    // set temporary target data
    target.setId(ptrTran->getDeliveredAccID());

    // check target in container
    bool check = clientContainer.retrieve(target, ptrClient);

    // perform transaction
    if (check) {
        ptrClient->deposit(ptrTran->getReceivedAccID()
            , ptrTran->getAmount());
    }

    // error transaction
    else {
        invalidTransactionContainer.enqueue(ptrTran);
    }

    // delete pointer
    delete ptrClient;
    ptrClient = nullptr;
}

// this function will be called in processTransactions function
void Manager::withdrawHelper(Transaction *ptrTran) {
    
    // pointer that hold a client data
    Client* ptrClient;

    // temporary target to check
    Client target;

    // set temporary target data
    target.setId(ptrTran->getDeliveredAccID());

    // check target in container
    bool check = clientContainer.retrieve(target, ptrClient);

    // perform transaction
    if (check) {
        ptrClient->withdraw(ptrTran->getDeliveredAccID()
            , ptrTran->getAmount());
    }

    // error transaction
    else {
        invalidTransactionContainer.enqueue(ptrTran);
    }

    // delete pointer
    delete ptrClient;
    ptrClient = nullptr;
}

// display transactions end of the day
void Manager::report()
{
    // error transaction
    invalidTransactions();

    // report summary
    accountSummary();
}

// display invalid transaction
void Manager::invalidTransactions() {

    // early exist
    if (invalidTransactionContainer.isEmpty())
        return;

    // pointer that hold an invalid transaction
    Transaction* ptrTransaction;

    // get invalid transaction
    while (invalidTransactionContainer.dequeue(ptrTransaction)) {
        
        // do something
        ///////////////////////////////////////////

        // delete ptr
        delete ptrTransaction;
        ptrTransaction = nullptr;
    }
}

// display account summary
void Manager::accountSummary() {

    // add code here
}
