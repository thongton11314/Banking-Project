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
bool Transaction::setData(ifstream& inFile) {

    inFile >> transType;
    if (transType == 'M') {
        inFile >> deliveredAccID >> amount >> receivedClientID;
        return true;
    }
    else if (transType == 'D' || transType == 'W') {
        inFile >> deliveredAccID >> amount;
        receivedAccID = deliveredAccID;
        return true;
    }
    else
        return false;
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
    return receivedClientID;
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
