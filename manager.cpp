#include <iostream>
#include "manager.h"

// build client container
void Manager::buildClients(ifstream & infile)
{
    Client* ptr;
    bool checkData;                       // read good data
    while (!infile.eof()) {

        ptr = new Client;

        checkData = ptr->setData(infile); // fill the client object
        
        // add valid client
        if (checkData)
            clientContainer.insert(ptr);
        
        // ignore invalid client
    }
}

// buil client transaction
void Manager::buildTransactions(ifstream & infile)
{
    Transaction* ptr;
    bool checkData;                       // read good data
    while (!infile.eof()) {

        ptr = new Transaction;

        checkData = ptr->setData(infile); // fill the transaction object
        
        // add valid transaction object
        if (checkData)
            transactionContainer.enqueue(ptr);
        
        // add invalid transaction object
        else
            invalidTransactionContainer.enqueue(ptr);
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
                break;

            // transaction type deposit
            case 'D':
                depositHelper(ptrTransaction);
                break;
            
            // transaction type withdraw
            case 'W':
                withdrawHelper(ptrTransaction);
                break;

            // in case
            default:
                break;

            // error transaction
            // another case other D,W,M is already 
            // handle in buildTransaction
            // when read transaction from file
        }
    }
   
    // set data to null pointer after finished work
    ptrTransaction = nullptr;
}

// this function will be called in processTransactions function
// if move same client ID, then client has withdraw/deposit history
void Manager::moveHelper(Transaction * ptrTran) {

    // pointer point to transaction data
    Client* ptrDeliver;
    Client* ptrReceiver;

    // temporary target to check
    Client deliverTarget;
    Client recieverTarget;

    // initialize temporary target
    deliverTarget.setId(ptrTran->getDeliveredClientID());
    recieverTarget.setId(ptrTran->getReceivedClientID());

    // check deliver target
    bool isDeliver = clientContainer.retrieve(deliverTarget, ptrDeliver);

    // check receiver target
    bool isReciever = clientContainer.retrieve(recieverTarget, ptrReceiver);

    // perfrom transaction
    if (isDeliver && isReciever) {

        // withdraw from deliver account
        if (ptrDeliver->withdraw(ptrTran->getDeliveredAccID()
            , ptrTran->getAmount())) {

            // add history
            ptrDeliver->addHistory(ptrTran);
        }

        // deposit to receiver account
        if (ptrReceiver->deposit(ptrTran->getReceivedAccID()
            , ptrTran->getAmount())) {
            
            // add history
            ptrDeliver->addHistory(new Transaction(*ptrTran));
        }        
    }

    // error tracsaction, unknown client
    else {
        ptrTran->setUnknownClient(true);
        invalidTransactionContainer.enqueue(ptrTran);
    }

    // set data to null pointer after finished work
    ptrDeliver = ptrReceiver = nullptr;
}

// this function will be called in processTransactions function
void Manager::depositHelper(Transaction *ptrTran) {

    // pointer that hold a client data
    Client* ptrClient;

    // temporary target to check
    Client target;

    // set temporary target data
    target.setId(ptrTran->getDeliveredClientID());

    // check target in container
    bool check = clientContainer.retrieve(target, ptrClient);

    // perform transaction
    if (check) {
        if (ptrClient->deposit(ptrTran->getDeliveredAccID()
            , ptrTran->getAmount())) {

            // add transaction history into client
            ptrClient->addHistory(ptrTran);
        }
    }

    // error transaction, unknown client
    else {
        ptrTran->setUnknownClient(true);
        invalidTransactionContainer.enqueue(ptrTran);
    }

    // set data to null pointer after finished work
    ptrClient = nullptr;
}

// this function will be called in processTransactions function
void Manager::withdrawHelper(Transaction *ptrTran) {
    
    // pointer that hold a client data
    Client* ptrClient;

    // temporary target to check
    Client target;

    // set temporary target data
    target.setId(ptrTran->getDeliveredClientID());

    // check target in container
    bool check = clientContainer.retrieve(target, ptrClient);

    // perform transaction
    if (check) {

        // sufficient fund
        if (ptrClient->withdraw(ptrTran->getDeliveredAccID()
            , ptrTran->getAmount())) {
            
            // add transaction history into client
            ptrClient->addHistory(ptrTran);
        }

        // unsufficient fund
        else {
            ptrTran->setSufficient(false);
            invalidTransactionContainer.enqueue(ptrTran);
        }
    }

    // error transaction, unknown client
    else {
        ptrTran->setUnknownClient(false);
        invalidTransactionContainer.enqueue(ptrTran);
    }

    ptrClient = nullptr;
}

// report
// show all invalid transaction, or account unsufficient fund,
// active clients have transaction, and summary report clients infor
void Manager::report()
{
    // this function has leak memory
    // error transaction
    invalidTransactions();
    cout << endl;

    // report summary
    clientSummary();
    cout << endl;

    // all client report
    clientsReport();
    cout << endl;
}

// display invalid transaction
void Manager::invalidTransactions() {

    // early exist
    if (invalidTransactionContainer.isEmpty())
        return;

    cout << "Error:" << endl;

    // pointer that hold an invalid transaction
    Transaction* ptrTransaction;
    
    // hold different type of error
    Queue invalidType;
    Queue insufficientFunds;
    Queue unknownClient;

    // sort invalid transaction
    while (invalidTransactionContainer.dequeue(ptrTransaction)) {
        
        // get invalid type of transaction
        if (ptrTransaction->getTranType() != 'D'
            && ptrTransaction->getTranType() != 'W'
            && ptrTransaction->getTranType() != 'M') {
            invalidType.enqueue(ptrTransaction);
        }

        // get insufficient transaction
        else if (ptrTransaction->isSufficient() == false) {
            insufficientFunds.enqueue(ptrTransaction);
        }
        
        // get unkown clients request
        else if (ptrTransaction->isUnknownClient() == true) {
            unknownClient.enqueue(ptrTransaction);
        }
    }

    // print out error in order
    // Invalid transaction
    if (!insufficientFunds.isEmpty()) {
    cout << "Invalid type of transaction:" << endl;
        while (invalidType.dequeue(ptrTransaction)) {
            cout << " - Could not define type '" <<
                ptrTransaction->getTranType()
                << "' transaction"
                << endl;
                delete ptrTransaction;
        }
    }

    // Insufficient transfer funds
    if (!insufficientFunds.isEmpty()) {
        cout << "Insufficient transfer funds:" << endl;
        while (insufficientFunds.dequeue(ptrTransaction)) {
            cout << " - Could not transfer funds between "
                << ptrTransaction->getDeliveredAccID()
                << " to "
                << ptrTransaction->getDeliveredAccID()
                << endl;
            delete ptrTransaction;
        }
    }

    // Unknown client request
    if (!unknownClient.isEmpty()) {
        cout << "Unknown client request:" << endl;
        while (unknownClient.dequeue(ptrTransaction)) {
            if (ptrTransaction->getDeliveredClientID() !=
                ptrTransaction->getReceivedClientID()) {
                cout << " - Could not defined client "
                    << ptrTransaction->getDeliveredClientID()
                    << " or "
                    << ptrTransaction->getReceivedClientID()
                    << endl;
            }
            else {
                cout << " - Could not defined client "
                    << ptrTransaction->getDeliveredClientID()
                    << endl;
            }
            delete ptrTransaction;
        }
    }

    ptrTransaction = nullptr;
}

// display client summary
// this only show the current client that has transaction actively
void Manager::clientSummary() {
    cout << "History of active clients:" << endl;
    cout << "In process" << endl;

}

// display clients report
// show all summary of clients information and their accounts
void Manager::clientsReport() {
    cout << "Clients summary:" << endl;
    
    cout << "Need different format" << endl;
    clientContainer.display();
}
