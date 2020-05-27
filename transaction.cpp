#include "transaction.h"

//----------------------------------------------------------------------------
// constructor
// initialize transaction to default number, which is 0
Transaction::Transaction() {

    // initialize transaction information
    deliveredClientID = -1;
    receivedClientID = -1;
    deliveredAccID = -1;
    receivedAccID = -1;
    amount = -1;
    transType = -1;
    sufficient = false;
}

//----------------------------------------------------------------------------
// copy constructor
// this transaction will be identical as copied transaction
Transaction::Transaction(const Transaction & other) {
    deliveredClientID = other.deliveredClientID;
    receivedClientID =  other.receivedClientID;
    deliveredAccID = other.deliveredAccID;
    receivedAccID = other.receivedAccID;
    amount = other.amount;
    transType = other.transType;
    sufficient = other.sufficient;
}

//----------------------------------------------------------------------------
// destructor
// used after each function to deallocate memory
Transaction::~Transaction() {}

//----------------------------------------------------------------------------
// setData
// sets all the values
// return true, valid typy of transaction
// return false, invalid type of transaction
bool Transaction::setData(ifstream& infile) {

    infile >> transType;

    // valid type transaction
    if (transType == 'M' || transType == 'D' || transType == 'W') {
        
        // move
        if (transType == 'M') {
            infile >> deliveredAccID >> amount >> receivedAccID;
        }

        //deposit or withdraw
        else {
            infile >> deliveredAccID >> amount;
            receivedAccID = deliveredAccID;
        }

        // set up for client ID
        deliveredClientID = deliveredAccID / 10;
        receivedClientID = receivedAccID / 10;
        sufficient = true;
        return true;
    }

    // invalid type of transaction
    else {
        char next;
        while (infile.get(next) && next != '\n'); // read until end statement
        return false;
    }
}

//----------------------------------------------------------------------------
// setSufficient
// to set if transaction is insufficient
void Transaction::setSufficient(bool set) {
    sufficient = set;
}

//----------------------------------------------------------------------------
// setUnknownClient
// to set if transaction is unknown client
void Transaction::setUnknownClient(bool set) {
    unknownClient = set;
}

//----------------------------------------------------------------------------
// getClientDeliveredID
// retrieves the ID of delivered client
int Transaction::getDeliveredClientID() const {

    return deliveredClientID;
}

//----------------------------------------------------------------------------
// getClientReceivedID
// retrieves the ID of delivered client
int Transaction::getReceivedClientID() const {
    return receivedClientID;
}

//----------------------------------------------------------------------------
// getAccDeliveredID
// retrieves the delivered account ID
int Transaction::getDeliveredAccID() const {

    return deliveredAccID;
}

//----------------------------------------------------------------------------
// getAccReceivedID
// retrieves the received account ID
int Transaction::getReceivedAccID() const {
    return receivedAccID;
}

//----------------------------------------------------------------------------
// getTranType
// retrieves the transaction type
char Transaction::getTranType() const {
    return transType;
}

//----------------------------------------------------------------------------
// getAmount
// retrieves the amount that the transaction is handling
int Transaction::getAmount() const {
    return amount;
}

//----------------------------------------------------------------------------
// isSufficient
// get information of transaction in case sufficient
bool Transaction::isSufficient() const {
    return sufficient;
}

//----------------------------------------------------------------------------
// isUnknownClient
// get information of transaction incase unknown client
bool Transaction::isUnknownClient() const {
    return unknownClient;
}

ostream & operator<<(ostream &output, const Transaction & obj) {
    if (obj.getTranType() == 'M') {
        output << obj.transType << setw(2)
            << obj.deliveredAccID << setw(2)
            << obj.amount << setw(2)
            << obj.receivedAccID << endl;
    }
    else {
        output << obj.transType << setw(2)
            << obj.deliveredAccID << setw(2)
            << obj.amount << endl;
    }
    return output;
}