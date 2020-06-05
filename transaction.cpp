#include "transaction.h"

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

Transaction::Transaction(const Transaction & other) {
    deliveredClientID = other.deliveredClientID;
    receivedClientID =  other.receivedClientID;
    deliveredAccID = other.deliveredAccID;
    receivedAccID = other.receivedAccID;
    amount = other.amount;
    transType = other.transType;
    sufficient = other.sufficient;
}

Transaction::~Transaction() {}

bool Transaction::setData(ifstream& infile) {

    infile >> transType;    
    if (transType == 'M' || transType == 'D' || transType == 'W') {
        if (transType == 'M') {
            infile >> deliveredAccID >> amount >> receivedAccID;
        }
        else {
            infile >> deliveredAccID >> amount;
            receivedAccID = deliveredAccID;
        }
        deliveredClientID = deliveredAccID / 10;
        receivedClientID = receivedAccID / 10;
        sufficient = true;
        return true;
    }
    else {
        char next;
        while (infile.get(next) && next != '\n');
        return false;
    }
}

void Transaction::setSufficient(bool set) {
    sufficient = set;
}

void Transaction::setUnknownClient(bool set) {
    unknownClient = set;
}

int Transaction::getDeliveredClientID() const {

    return deliveredClientID;
}

int Transaction::getReceivedClientID() const {
    return receivedClientID;
}

int Transaction::getDeliveredAccID() const {

    return deliveredAccID;
}

int Transaction::getReceivedAccID() const {
    return receivedAccID;
}

char Transaction::getTranType() const {
    return transType;
}

int Transaction::getAmount() const {
    return amount;
}

bool Transaction::isSufficient() const {
    return sufficient;
}

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
