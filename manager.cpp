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

    Transaction* ptrTran;
    Client* ptrClientOne;
    Client* ptrClientTwo;

    // temporary target
    Client targetOne;   // used for deposit and withdraw
    Client targetTwo;   // used for move in case

    while (transactionContainer.dequeue(ptrTran)) {

        // transaction type of move
        if (ptrTran->getTranType() == 'M') {        

            // initialize temporary target
            targetOne.setClientId(ptrTran->getClientIDOne());
            targetTwo.setClientId(ptrTran->getClientIDTwo());
            
            // check deliver target
            bool checkOne = clientContainer.retrieve(targetOne, ptrClientOne);
            
            // check receiver target
            bool checkTwo = clientContainer.retrieve(targetTwo, ptrClientTwo);

            // perfrom transaction
            if (checkOne && checkTwo) {

                // withdraw from deliver account
                ptrClientOne->withdraw(ptrTran->getAccIDOne()
                    , ptrTran->getAmount());

                // deposit to receiver account
                ptrClientTwo->deposit(ptrTran->getAccIDTwo()
                    , ptrTran->getAmount());

                // add history transaction into deliver account
                ptrClientOne->addHistory(*ptrTran);
            }

            // error performing tracsaction
            else {

                // add unidentified transaction
                // add code here
                /////////////////////////////////////////
            }
            
        }

        // transaction type deposit
        else if (ptrTran->getTranType() == 'D') {

            // initialize temporary target
            targetOne.setClientId(ptrTran->getClientIDOne());
            
            // check target in container
            bool check = clientContainer.retrieve(targetOne, ptrClientOne);

            // perform transaction
            if (check) {
                ptrClientOne->deposit(ptrTran->getAccIDOne(), 
                    ptrTran->getAmount());
            }

            // error performing transaction
            else {

                // add unidentified transaction
                // add code here
                /////////////////////////////////////////
            }
        }

        // transaction type withdraw
        else if (ptrTran->getTranType() == 'W') {

            // initialize temporary target
            targetOne.setClientId(ptrTran->getClientIDOne());

            // check target in container
            bool check = clientContainer.retrieve(targetOne, ptrClientOne);
            
            // perfrom transaction
            if (check) {
                ptrClientOne->deposit(ptrTran->getAccIDOne(),
                    ptrTran->getAmount());
            }

            // error performing transaction
            else {

                // add unidentified transaction
                // add code here
                /////////////////////////////////////////
            }
        }

        // invalid transaction type
        else {

           // add unidentified transaction
           // add code here
           /////////////////////////////////////////
        }

        // delete pointer
        delete ptrClientOne;
        ptrClientOne = nullptr;
        delete ptrClientTwo;
        ptrClientTwo = nullptr;
    }
}

// display transactions end of the day
void Manager::displayReport() const
{
    // get each client from client container

    // display its transactions
}
