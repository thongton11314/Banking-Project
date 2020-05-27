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

// false if client ID is less than 1 or exceed 9999
bool Client::setData(ifstream & inFile) {

    // set up first name, last name, id
    inFile >> lastName >> firstName >> clientID;

    // early exit if client id is not in range 1-9999
    if (clientID < MINID || clientID > MAXID)
        return false;

    // using for setting up start balance
    int amount = 0;

    // not negative balance
    bool valid = true;

    // set up for start account balance
    for (int i = 0; i < MAXACCOUNT && valid; i++) {
        inFile >> amount;

        // valid amount that positive balance
        if (amount >= 0)
            loseAccount[i].setStartBalance(amount);

        // invalid amount that negative balance
        else
            valid = false;
    }

    // return true if all balance is valid number
    return valid;
}

bool Client::deposit(int accIndex, int val) {

    // convert into tenth account by get last digit
    accIndex = accIndex % CONVERTED;
    if (accIndex >= 0 && accIndex < MAXACCOUNT) {
        return loseAccount[accIndex].adjustBalance(+val);
    }

    // account out of bounce
    return false;
}

bool Client::withdraw(int accIndex, int val) {

    // convert into tenth account by get last digit
    accIndex = accIndex % CONVERTED;
    if (accIndex > 0 && accIndex < MAXACCOUNT) {

        // sufficient fund
        if (loseAccount[accIndex].adjustBalance(-val))
            return true;
        
        // unsufficient fund
        else
            return false;
    }

    // account out of bounce
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
    // print out start account balance
    for (int i = 0; i < MAXACCOUNT; i++) {

        // count how many digit for setwidth
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
    // print out current account balance
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