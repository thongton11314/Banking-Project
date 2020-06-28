#include "client.h"

//----------------------------------------------------------------------------
// constructor 
// initialize client by default
Client::Client() {
    lastName = "default";
    firstName = "default";
    clientID = -1;
}

//----------------------------------------------------------------------------
// deconstructor
// used after each function to deallocate memory
Client::~Client() {}

//----------------------------------------------------------------------------
// setID
// set client ID
void Client::setId(int id) {
    clientID = id;
}

//----------------------------------------------------------------------------
// setData
// will take fstream as parameter and fill out client information in file
// return true if valid data such as good id and positive balance
//        false if client ID is less than 1 or exceed 9999
bool Client::setData(ifstream & infile) {

    // set up first name, last name, id
    infile >> lastName >> firstName;
   
    // if client id is not digit or out of range 1-9999 return false
    infile >> clientID;
    if (infile.fail() || clientID < MINID || clientID > MAXID) {

        // read until end of statement in file
        infile.clear(); // clean bad data
        char temp;
        while (infile.get(temp) && temp != '\n');
        return false;
    }

    // set up for start account balance
    int amount = 0;     // using for setting up start balance
    bool valid = true;  // not negative balance
    for (int i = 0; i < MAXACCOUNT && valid; i++) {
        infile >> amount;

        if (infile.fail() || amount < 0) {
            infile.clear(); // clean bad data
            valid = false;
        }

        // valid amount that positive balance
        else {
            loseAccount[i].setInitialBalance(amount);
        }
    }

    // read until end of statement in file
    if (!valid) {
        infile.clear(); // clean bad data
        char temp;
        while (infile.get(temp) && temp != '\n');
        return false;
    }

    // return true if good data
    return valid;
}

//----------------------------------------------------------------------------
// deposit
// will take account type and balance to add up balance of accounts
// first parameter is account index
// second parameter is amount
// return true if deposit successfully
//        false if fail to deposit
bool Client::deposit(int accIndex, int val) {

    // convert into tenth account by get last digit
    accIndex = accIndex % CONVERTED;
    if (accIndex >= 0 && accIndex < MAXACCOUNT) {
        loseAccount[accIndex].adjustBalance(+val);
        return true;
    }

    // account out of bounce
    return false;
}

//----------------------------------------------------------------------------
// withdraw
// will take account type and balance to decrease balance of accounts
// first parameter is account index
// second parameter is amount
// return true if withdraw successfully
//        false if out of account bounce or account balance approach 0
bool Client::withdraw(int accIndex, int val) {

    // convert into tenth account by get last digit
    accIndex = accIndex % CONVERTED;

    // early exit, out of account range
    if (accIndex < 0 || accIndex > MAXACCOUNT) {
        return false;
    }

    // money market account
    // 0: Money Market
    // 1: Prime Money Market
    if (accIndex >= 0 && accIndex <= 1) {
        int account0 = loseAccount[0].getFinalBalance();
        int account1 = loseAccount[1].getFinalBalance();

        // get total balance of both account
        int bothBalance = account0 + account1;

        // not enough money to withdraw
        if (val > bothBalance) {
            return false;
        }

        // if enough to withdraw
        else {

            // case Money Market
            if (accIndex == 0) {
                if (val > account0) {
                    loseAccount[0].adjustBalance(-account0);
                    loseAccount[1].adjustBalance(-(val - account0));
                    return true;
                }
                else {
                    loseAccount[0].adjustBalance(-val);
                    return true;
                }
            }

            // case Prime Money Market
            else {
                if (val > account1) {
                    loseAccount[1].adjustBalance(-account1);
                    loseAccount[0].adjustBalance(-(val - account1));
                    return true;
                }
                else {
                    loseAccount[1].adjustBalance(-val);
                    return true;
                }
            }
        }
    }

    // bond account
    // 2 : Long - Term Bond
    // 3 : Short - Term Bond
    else if (accIndex >= 2 && accIndex <= 3) {

        int account2 = loseAccount[2].getFinalBalance();
        int account3 = loseAccount[3].getFinalBalance();

        // get total balance of both account
        int bothBalance = account2 + account3;

        // not enough money to withdraw
        if (val > bothBalance) {
            return false;
        }

        // if enough to withdraw
        else {

            // case Money Market
            if (accIndex == 2) {
                if (val > account2) {
                    loseAccount[2].adjustBalance(-account2);
                    loseAccount[3].adjustBalance(-(val - account2));
                    return true;
                }
                else {
                    loseAccount[2].adjustBalance(-val);
                    return true;
                }
            }

            // case Prime Money Market
            else {
                if (val > account3) {
                    loseAccount[3].adjustBalance(-account3);
                    loseAccount[2].adjustBalance(-(val - account3));
                    return true;
                }
                else {
                    loseAccount[3].adjustBalance(-val);
                    return true;
                }
            }
        }
    }

    // other account can not be cover when over withdraw
    else {
        return loseAccount[accIndex].adjustBalance(-val);
    }

    // other case will return false
    return false;
}

//----------------------------------------------------------------------------
// getLastName
// return last name of client
string Client::getLastName() const {
    return lastName;
}

//----------------------------------------------------------------------------
// getFirstName
// return first name of client
string Client::getFirstName() const {
    return firstName;
}

//----------------------------------------------------------------------------
// getID
// return ID of client
int Client::getId() const {
    return clientID;
}

//----------------------------------------------------------------------------
// getInitialBalance
// return initial balance of client
int Client::getInitialBalance(int accIndex) const {
    return loseAccount[accIndex].getInitialBalance();
}

//----------------------------------------------------------------------------
// getFinalBalance
// return final balance of client
int Client::getFinalBalance(int accIndex) const {
    return loseAccount[accIndex].getFinalBalance();
}

//----------------------------------------------------------------------------
// addHistory
// add history transaction to client
bool Client::addHistory(Transaction * obj) {
    return historyContainer.enqueue(obj);
}

//----------------------------------------------------------------------------
// isEmptyHistory
// check client history empty or not
bool Client::isEmptyHistory() const {
    return historyContainer.isEmpty();
}

//----------------------------------------------------------------------------
// displayHistory
// diplay client history
void Client::displayHistory() {
    cout << historyContainer;
}

//----------------------------------------------------------------------------
// operator<
// compare less than 
bool Client::operator<(const Client & other) const {
    return clientID < other.clientID;
}

//----------------------------------------------------------------------------
// operator<=
// compare less than or equal
bool Client::operator<=(const Client & other) const {
    return clientID <= other.clientID;
}

//----------------------------------------------------------------------------
// operator>
// compare greater
bool Client::operator>(const Client & other) const {
    return clientID > other.clientID;
}

//----------------------------------------------------------------------------
// operator>=
// compare greater or euqual
bool Client::operator>=(const Client & other) const {
    return clientID >= other.clientID;
}

//----------------------------------------------------------------------------
// operator==
// compare equal
bool Client::operator==(const Client & other) const {
    return clientID == other.clientID;
}

//----------------------------------------------------------------------------
// operator!=
// compare not equal
bool Client::operator!=(const Client & other) const {
    return clientID != other.clientID;
}

//----------------------------------------------------------------------------
// operator<<
// print out the information of client, include initial and final balance
ostream & operator<<(ostream& output, const Client& obj) {

    // print client id first name, last name
    output << "-" << " Client Id: " 
        << obj.clientID
        << setw(3) << " " << obj.firstName
        << setw(2) << " " << obj.lastName
        << endl;

    // print out initial account balance
    output << setw(2) << " " << "Initial balance:";
    for (int i = 0; i < MAXACCOUNT; i++) {
        output << setw(6) << obj.loseAccount[i].getInitialBalance();
    }
    output << endl;

    // print out final account balance
    output << setw(2) << " " << "Final balance:  ";
    for (int i = 0; i < MAXACCOUNT; i++) {
        output << setw(6) << obj.loseAccount[i].getFinalBalance();
    }
    output << endl;
    return output;
}