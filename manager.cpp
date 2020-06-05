#include <iostream>
#include "manager.h"

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
        }
    }
   
    // set data to null pointer after finished work
    ptrTransaction = nullptr;
}

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

void Manager::depositHelper(Transaction *ptrTran) {
    Client* ptrClient;
    Client target;
    target.setId(ptrTran->getDeliveredClientID());
    bool check = clientContainer.retrieve(target, ptrClient);
    if (check) {
        if (ptrClient->deposit(ptrTran->getDeliveredAccID()
            , ptrTran->getAmount())) {
            ptrClient->addHistory(ptrTran);
        }
    }
    else {
        ptrTran->setUnknownClient(true);
        invalidTransactionContainer.enqueue(ptrTran);
    }
    ptrClient = nullptr;
}

void Manager::withdrawHelper(Transaction *ptrTran) {
    Client* ptrClient;
    Client target;
    target.setId(ptrTran->getDeliveredClientID());
    bool check = clientContainer.retrieve(target, ptrClient);
    if (check) {
        if (ptrClient->withdraw(ptrTran->getDeliveredAccID()
            , ptrTran->getAmount())) {
            ptrClient->addHistory(ptrTran);
        }
        else {
            ptrTran->setSufficient(false);
            invalidTransactionContainer.enqueue(ptrTran);
        }
    }
    else {
        ptrTran->setUnknownClient(false);
        invalidTransactionContainer.enqueue(ptrTran);
    }

    ptrClient = nullptr;
}

void Manager::report()
{
    invalidTransactions();
    cout << endl;
    clientSummary();
    cout << endl;
    clientsReport();
    cout << endl;
}

void Manager::invalidTransactions() {  
    if (invalidTransactionContainer.isEmpty())
        return;
    cout << "Error:" << endl;
    Transaction* ptrTransaction;
    Queue invalidType;
    Queue insufficientFunds;
    Queue unknownClient;
    while (invalidTransactionContainer.dequeue(ptrTransaction)) {
        if (ptrTransaction->getTranType() != 'D'
            && ptrTransaction->getTranType() != 'W'
            && ptrTransaction->getTranType() != 'M') {
            invalidType.enqueue(ptrTransaction);
        }
        else if (ptrTransaction->isSufficient() == false) {
            insufficientFunds.enqueue(ptrTransaction);
        }
        else if (ptrTransaction->isUnknownClient() == true) {
            unknownClient.enqueue(ptrTransaction);
        }
    }
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
void Manager::clientSummary() {
    cout << "History of active clients:" << endl;
    cout << "In process" << endl;

}
void Manager::clientsReport() {
    cout << "Clients summary:" << endl;
    
    cout << "Need different format" << endl;
    clientContainer.display();
}
