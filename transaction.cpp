#include "transaction.h"

//----------------------------------------------------------------------------
// constructor
// initialize transaction to default number, which is -1
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
bool Transaction::setData(ifstream& infile) {

    infile >> transType;

    // check if valid type
    bool valid = true;

    // valid type transaction move, deposit, withdraw
    if (transType == 'D' || transType == 'd'
        || transType == 'W' || transType == 'w'
        || transType == 'M' || transType == 'm') {
       
        // read deliver acc id, and amount
        infile >> deliveredAccID >> amount;

        // move
        if (transType == 'M' || transType == 'm') {
            infile >> receivedAccID;
        }

        //deposit or withdraw
        else {
            receivedAccID = deliveredAccID;
        }

        // set up for client ID
        deliveredClientID = deliveredAccID / 10;
        receivedClientID = receivedAccID / 10;
    }

    // history transaction
    else if (transType == 'H' || transType == 'h') {

        // present for client id
        infile >> deliveredClientID;
        receivedClientID = deliveredClientID;
    }
    
    // invalid type of transaction
    else {
        valid = false;
    }

    // read until end of statement in case invalid transaction
    infile.clear();
    char temp;
    while (infile.get(temp) && temp != '\n');
    return valid;
}

//----------------------------------------------------------------------------
// setTransType
// set transaction type
void Transaction::setTransType(char type) {
    transType = type;
}

//----------------------------------------------------------------------------
// setAmount
// set transaction amount
void Transaction::setAmount(int val) {
    amount = val;
}

//----------------------------------------------------------------------------
// setDeliveredClientID
// set deliver client ID
void Transaction::setDeliveredClientID(int val) {
    deliveredClientID = val;
}

//----------------------------------------------------------------------------
// setReceivedClientID
// set received client ID
void Transaction::setReceivedClientID(int val) {
    receivedClientID = val;
}

//----------------------------------------------------------------------------
// setDeliveredAccID
// set deliver account ID
void Transaction::setDeliveredAccID(int val) {
    deliveredAccID = val;
}

//----------------------------------------------------------------------------
// setReceivedAccID
// set received account ID
void Transaction::setReceivedAccID(int val) {
    receivedAccID = val;
}

//----------------------------------------------------------------------------
// getDeliveredClientID
// retrieves the ID of delivered client
int Transaction::getDeliveredClientID() const {
    return deliveredClientID;
}

//----------------------------------------------------------------------------
// getReceivedClientID
// retrieves the ID of delivered client
int Transaction::getReceivedClientID() const {
    return receivedClientID;
}

//----------------------------------------------------------------------------
// getDeliveredAccID
// retrieves the delivered account ID
int Transaction::getDeliveredAccID() const {
    return deliveredAccID;
}

//----------------------------------------------------------------------------
// getReceivedAccID
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
// accDescription
// will get account desciption from range 0-9
// example: input 11110 will print "Prime Money Market"
void Transaction::accDescription(int accID) const {
    accID = accID % 10; // get the last digit of account ID

    // check range
    if (accID >= 0 && accID <= 9) {
        switch (accID) {
        case 0:
            cout << "Money Market";
            break;
        case 1:
            cout << "Prime Money Market";
            break;
        case 2:
            cout << "Long-Term Bond";
            break;
        case 3:
            cout << "Short-Term Bond";
            break;
        case 4:
            cout << "500 Index Fund";
            break;
        case 5:
            cout << "Capital Value Fund";
            break;
        case 6:
            cout << "Growth Equity Fund";
            break;
        case 7:
            cout << "Growth Index Fund";
            break;
        case 8:
            cout << "Value Fund";
            break;
        case 9:
            cout << "Value Stock Index";
            break;
        default:
            cout << "error account";
            break;
        }
    }
}

//----------------------------------------------------------------------------
// operator<<
// print out transaction type and amount
ostream & operator<<(ostream &output, const Transaction & obj) {
    if (obj.getTranType() == 'M') {
        output << setw(2) << " "
            << "Move"
            << setw(7) << "$"
            << setw(8) << obj.amount
            << setw(7) << "from ";
        obj.accDescription(obj.getDeliveredAccID());
        output << endl;
        output << setw(26) << "to "; 
        obj.accDescription(obj.getReceivedAccID());
        if (obj.getDeliveredClientID() != obj.getReceivedClientID()) {
            output << " of client ID:" << obj.getReceivedClientID();
        }
        else {
            output << " of this client";
        }
    }
    else if (obj.getTranType() == 'D'){
        output << setw(2) << " "
            << "Deposit"
            << setw(4) << "$" 
            << setw(8) << obj.amount
            << setw(5) << "to ";
        obj.accDescription(obj.getDeliveredAccID());
    }
    else {
        output << setw(2) << " "
            << "Withdraw"
            << setw(3) << "$"
            << setw(8) << obj.amount
            << setw(7) << "from ";
        obj.accDescription(obj.getDeliveredAccID());
    }
    return output;
}