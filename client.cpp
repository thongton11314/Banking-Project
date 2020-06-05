#include "client.h"

Client::Client() {
    firstName = "default";
    lastName = "default";
    clientID = 0;
}

Client::~Client() {}

Client::Client(const Client & other) {
    firstName = other.firstName;
    lastName = other.lastName;
    clientID = other.clientID;
    for (int i = 0; i < MAXACCOUNT; i++) {
        loseAccount[i] = other.loseAccount[i];
    }
}

void Client::setId(int id) {
    clientID = id;
}

bool Client::setData(ifstream & inFile) {
    inFile >> lastName >> firstName >> clientID;
    if (clientID < MINID || clientID > MAXID)
        return false;
    int amount = 0;
    bool valid = true;
    for (int i = 0; i < MAXACCOUNT && valid; i++) {
        inFile >> amount;
        if (amount >= 0)
            loseAccount[i].setStartBalance(amount);
        else
            valid = false;
    }
    return valid;
}

bool Client::deposit(int accIndex, int val) {
    accIndex = accIndex % CONVERTED;
    if (accIndex >= 0 && accIndex < MAXACCOUNT) {
        return loseAccount[accIndex].adjustBalance(+val);
    }
    return false;
}

bool Client::withdraw(int accIndex, int val) {
    accIndex = accIndex % CONVERTED;
    if (accIndex > 0 && accIndex < MAXACCOUNT) {
        if (loseAccount[accIndex].adjustBalance(-val))
            return true;        
        else
            return false;
    }
    return false;
}

int Client::getId() const {
    return clientID;
}

int Client::getStartBalance(int accIndex) const {
    return loseAccount[accIndex].getStartBalance();
}

int Client::getFinalBalance(int accIndex) const {
    return loseAccount[accIndex].getFinalBalance();
}

void Client::addHistory(Transaction * obj) {
    historyContainer.enqueue(obj);
}

Client & Client::operator=(const Client & other) {
    if (this != &other) {
        firstName = other.firstName;
        lastName = other.lastName;
        clientID = other.clientID;
        for (int i = 0; i < MAXACCOUNT; i++) {
            loseAccount[i] = other.loseAccount[i];
        }
    }
    return *this;
}

bool Client::operator<(const Client & other) const {
    return clientID < other.clientID;
}

bool Client::operator<=(const Client & other) const {
    return clientID <= other.clientID;
}

bool Client::operator>(const Client & other) const {
    return clientID > other.clientID;
}

bool Client::operator>=(const Client & other) const {
    return clientID >= other.clientID;
}

bool Client::operator==(const Client & other) const {
    return clientID == other.clientID;
}

bool Client::operator!=(const Client & other) const {
    return clientID != other.clientID;
}

ostream & operator<<(ostream& output, const Client& obj)
{
    // print last name, first name, client id
    output << obj.lastName << " "
        << obj.firstName << " "
        << obj.clientID
        << endl;
    output << " Start balance:";
    for (int i = 0; i < MAXACCOUNT; i++) {
        int n = obj.loseAccount[i].getStartBalance();
        int count = 0;
        n < 10 ? ++count : count;
        while (n != 0) {
            n = n / 10;
            ++count;
        }

        output << setw(count + 1) << obj.loseAccount[i].getStartBalance();
    }
    output << endl;

    output << " Final balance:";
    for (int i = 0; i < MAXACCOUNT; i++) {

        // count how many digit for setwidth
        int n = obj.loseAccount[i].getFinalBalance();
        int count = 0;
        n < 10 ? ++count : count;
        while (n != 0) {
            n = n / 10;
            ++count;
        }

        output << setw(count + 1) << obj.loseAccount[i].getFinalBalance();
    }
    output << endl;
    return output;
}
