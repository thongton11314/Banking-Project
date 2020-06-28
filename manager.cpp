#include "manager.h"

//----------------------------------------------------------------------------
// constructor
Manager::Manager() {}; 

//----------------------------------------------------------------------------
// destructor
Manager::~Manager() {};

//----------------------------------------------------------------------------
// buildClients
// build client container
// only read good value, ignore the invalid client input
void Manager::buildClients(ifstream & infile) {
    
    // early exit, and show error message that can not be read
    if (!infile) {
        cout << "Could not read client file" << endl;
        return;
    }
    
    Client* ptr;
    bool checkData;                       // used for reading good data
    while (!infile.eof()) {
        ptr = new Client;                 // create new client object
        
        // must have setData implementation of client
        checkData = ptr->setData(infile); // fill the client object
        
        // add valid client
        if (checkData) {

            // if not duplicate then insert, otherwise ignore
            if (!clientContainer.insert(ptr)) {
                delete ptr;
            }
        }
        
        // ignore invalid client
        else {
            delete ptr;
        }
    }
}

//----------------------------------------------------------------------------
// buildTransactions
// build client transaction command from the file
// only read good value such as type of transaction D, W, M, H
// put valid transaction into transaction container
// otherwise put invalid transaction into error transaction
void Manager::buildTransactions(ifstream & infile) {
    
    // early exit, and show error message that can not be read
    if (!infile) {
        cout << "Could not read command file" << endl;
        return;
    }
    
    Transaction* ptrTran;
    bool checkData;                           // read good data
    while (!infile.eof()) {

        ptrTran = new Transaction;            // create new transaction

        // must have setData implementation of transaction
        checkData = ptrTran->setData(infile); // fill the transaction object
        
        // add valid transaction
        if (checkData) {
            transactionContainer.enqueue(ptrTran);
        }
        
        // add invalid transaction
        else
            errorTransactions.enqueue(ptrTran);
    }
}

//----------------------------------------------------------------------------
// processTransactions
// process transactions from transaction container.
// it will perform transaction type of D, W, M, H.
// if the transaction type history, then print out that client history
// after all transaction process, shows error message of invalid transaction
void Manager::processTransactions()
{
    // early exist
    if (transactionContainer.isEmpty()) {
        cout << "No transaction to process." << endl;
        return;
    }

    // pointer that used for holding data
    Transaction* ptrTran;

    // get data from container
    while (transactionContainer.dequeue(ptrTran)) {

        switch (ptrTran->getTranType()) {
            
            // transaction type move
            case 'M':
                move(ptrTran);
                break;
            case 'm':
                move(ptrTran);
                break;

            // transaction type deposit
            case 'D':
                deposit(ptrTran);
                break;
            case 'd':
                deposit(ptrTran);
                break;
            
            // transaction type withdraw
            case 'W':
                withdraw(ptrTran);
                break;
            case 'w':
                withdraw(ptrTran);
                break;
            
            // transaction type history
            case 'H':
                history(ptrTran);
                break;
            case 'h':
                history(ptrTran);
                break;

            // in case error transaction
            default:
                break;
        }
    }
   
    // set data to null pointer after finished work
    ptrTran = nullptr;

    // error transaction
    invalidTransactions();
    cout << endl;
}

//----------------------------------------------------------------------------
// move
// if move same client ID, then client has move history only
// if move different client ID, then deliver client has transaction move
//                                   reciever client has transaction deposit
// this function will be called in processTransactions function
void Manager::move(Transaction * ptrTran) {

    // early check valid amount
    if (ptrTran->getAmount() <= 0) {
        errorInsufficientFunds.enqueue(ptrTran);
        return;
    }

    // temporary pointer that use get client data
    Client* ptrDeliver;
    Client* ptrReceiver;

    // temporary client object that use as target
    Client deliverTarget;
    Client recieverTarget;

    // initialize temporary target
    deliverTarget.setId(ptrTran->getDeliveredClientID());
    recieverTarget.setId(ptrTran->getReceivedClientID());

    // check deliver target
    bool isDeliver;
    isDeliver = clientContainer.retrieve(deliverTarget, ptrDeliver);

    // check receiver target
    bool isReciever;
    isReciever = clientContainer.retrieve(recieverTarget, ptrReceiver);

    // perfrom transaction
    if (isDeliver && isReciever) {

        // withdraw from deliver account
        if (ptrDeliver->withdraw(ptrTran->getDeliveredAccID()
            , ptrTran->getAmount())) {

            // add history type move for deliver account
            ptrDeliver->addHistory(ptrTran);

            // deposit to receiver account
            ptrReceiver->deposit(ptrTran->getReceivedAccID()
                , ptrTran->getAmount());

            // not internal transfer
            if (ptrTran->getDeliveredClientID()
                != ptrTran->getReceivedClientID()) {

                // add history type deposit for reciever account
                Transaction* depositTrans = new Transaction();
                depositTrans->setDeliveredClientID(ptrReceiver->getId());
                depositTrans->setDeliveredAccID(ptrTran->getReceivedAccID());
                depositTrans->setReceivedClientID(ptrReceiver->getId());
                depositTrans->setReceivedAccID(ptrTran->getReceivedAccID());
                depositTrans->setAmount(ptrTran->getAmount());
                depositTrans->setTransType('D');
                ptrReceiver->addHistory(depositTrans);
            }
        }

        // not enough money
        else {
            errorInsufficientFunds.enqueue(ptrTran);
        }
    }

    // error transaction, unknown client
    else {
        errorUnknownClients.enqueue(ptrTran);
    }

    // assign to null to be safe after finish work
    ptrDeliver = ptrReceiver = nullptr;
}

//----------------------------------------------------------------------------
// deposit
// this function will be called in processTransactions function
// it will perform deposit transaction in here
void Manager::deposit(Transaction * ptrTran) {

    // early check valid amount
    if (ptrTran->getAmount() <= 0) {
        errorInsufficientFunds.enqueue(ptrTran);
        return;
    }

    // temporary pointer that use get client data
    Client* ptrClient;

    // temporary client object that use as target
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
        errorUnknownClients.enqueue(ptrTran);
    }

    // assign to null to be safe after finish work
    ptrClient = nullptr;
}

//----------------------------------------------------------------------------
// withdraw
// it will perform withdraw transaction in here
// this function will be called in processTransactions function
void Manager::withdraw(Transaction * ptrTran) {
    
    // early check valid amount
    if (ptrTran->getAmount() <= 0) {
        errorInsufficientFunds.enqueue(ptrTran);
        return;
    }

    // temporary pointer that use get client data
    Client* ptrClient;

    // temporary client object that use as target
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
            errorInsufficientFunds.enqueue(ptrTran);
        }
    }

    // error transaction, unknown client
    else {
        errorUnknownClients.enqueue(ptrTran);
    }

    // assign to null to be safe after finish work
    ptrClient = nullptr;
}

//----------------------------------------------------------------------------
// history
// it will put the specific client transaction into history container
// this function will be called in processTransactions function
void Manager::history(Transaction * ptrTran) {
    
    // set up for retrieved client
    Client* ptrClient;

    // set up for client target
    Client target;
    target.setId(ptrTran->getDeliveredClientID());

    // look for the target
    if (clientContainer.retrieve(target, ptrClient)) {

        // format the history
        cout << "HISTORY" << endl;
        cout << "- Client: "
            << ptrClient->getLastName() << " "
            << ptrClient->getFirstName() << " "
            << ptrClient->getId() << endl;

        // client has no transaction
        if (ptrClient->isEmptyHistory()) {
            cout << setw(2) << " " << "Empty transaction" << endl << endl;
        }

        // client has transaction
        else {
            cout << setw(2) << " " << "Type"
                << setw(6) << " " << "Amount"
                << setw(5) << " " << "Detail" 
                << endl;
            cout << setw(2) << " " << "--------"
                << setw(2) << " " << "---------"
                << setw(2) << " " << "------------------------------------"
                << endl;

            // display type of transaction and amount
            ptrClient->displayHistory();
            cout << endl;
        }

        // delete pointer afete
        delete ptrTran;
        ptrTran = nullptr;
        ptrClient = nullptr;
    }

    // target to get history not found, handle this transaction as error
    else {
        errorUnknownClients.enqueue(ptrTran);
    }
}

//----------------------------------------------------------------------------
// invalidTransactions
// display invalid transaction
// this function will be called in processTransaction
void Manager::invalidTransactions() {

    // check if any error
    if (!errorTransactions.isEmpty()
        || !errorInsufficientFunds.isEmpty()
        || !errorUnknownClients.isEmpty()) {
        cout << "ERROR:" << endl;
    }

    // pointer that hold an invalid transaction
    Transaction* ptrTransaction;

    // print out error in order
    // Invalid transaction
    if (!errorTransactions.isEmpty()) {
        cout << "- Invalid transaction:" << endl;
        while (errorTransactions.dequeue(ptrTransaction)) {
            cout << setw(2) << " " << "Cannot define type '"
                << ptrTransaction->getTranType()
                << "' transaction";
            cout << endl;
            delete ptrTransaction;
        }
    }

    // Insufficient transfer funds
    if (!errorInsufficientFunds.isEmpty()) {
        cout << "- Insufficient transaction:" << endl;
        while (errorInsufficientFunds.dequeue(ptrTransaction)) {

            // amount less than zero
            if (ptrTransaction->getAmount() < 0) {
                cout << setw(2) << " " <<
                "Cannot perform negative transaction";
                cout << " of client ID: " << 
                ptrTransaction->getDeliveredClientID();
            }

            // amount is zero
            else if (ptrTransaction->getAmount() == 0) {
                cout << setw(2) << " " << "Cannot perform zero transaction";
                cout << " of client ID: " << 
                ptrTransaction->getDeliveredClientID();
            }

            // amount not zero, but not enough momey from their account
            else {

                // Cannot move money
                if (ptrTransaction->getDeliveredAccID()
                    != ptrTransaction->getReceivedAccID()) {
                    cout << setw(2) << " " << "Cannot transfer from ";
                    ptrTransaction->accDescription(ptrTransaction->
                                                   getDeliveredAccID());
                    cout << " of client ID: "
                        << ptrTransaction->getDeliveredClientID() << endl;
                    cout << setw(20) << " " << "to ";
                    ptrTransaction->accDescription(ptrTransaction->
                                                   getReceivedAccID());
                    cout << " of client ID: "
                        << ptrTransaction->getReceivedClientID();
                }

                // Cannot withdraw money
                else {
                    cout << setw(2) << " " << "Cannot withdraw from ";
                    ptrTransaction->accDescription(ptrTransaction->
                                                   getDeliveredAccID());
                    cout << " of client ID: "
                        << ptrTransaction->getDeliveredClientID();
                }
            }
            cout << endl;
            delete ptrTransaction;
        }
    }

    // Unknown client request
    if (!errorUnknownClients.isEmpty()) {
        cout << "- Unknown client:" << endl;
        while (errorUnknownClients.dequeue(ptrTransaction)) {
            if (ptrTransaction->getDeliveredClientID() !=
                ptrTransaction->getReceivedClientID()) {
                cout << setw(2) << " " << "Cannot defined client "
                    << ptrTransaction->getDeliveredClientID()
                    << " or "
                    << ptrTransaction->getReceivedClientID()
                    << endl;
            }
            else {
                cout << setw(2) << " " << "Cannot defined client "
                    << ptrTransaction->getDeliveredClientID()
                    << endl;
            }
            delete ptrTransaction;
        }
    }
    ptrTransaction = nullptr;
}

//----------------------------------------------------------------------------
// report
// show summary clients account status, initial and final balance
void Manager::report() {
    
    // clients report
    if (!clientContainer.isEmpty()) {
        cout << "REPORT" << endl;
        clientContainer.display();
    }
}