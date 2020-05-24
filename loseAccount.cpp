#include "loseAccount.h"

//----------------------------------------------------------------------------
// constructor
// constructs things
LOSEAccount::LOSEAccount() {
    currentBalance = 0;
    startBalance = 0;
}

//----------------------------------------------------------------------------
// destructor
// used after each function to deallocate memory
LOSEAccount::~LOSEAccount() {}

//----------------------------------------------------------------------------
// setStartBalance
// sets the starting value of an account
bool LOSEAccount::setStartBalance(int val) {

    //controls for negative values
    if (val < 0) {
        startBalance = 0;
        return false;
    }
    startBalance = val;
    return true;
}

//----------------------------------------------------------------------------
// adjustBalance
// adjusts the currentBalance value
bool LOSEAccount::adjustBalance(int val) {

    //controls for negative output
    if ((currentBalance + val) < 0) {
        return false;
    }
    currentBalance += val;
    return true;
}

//----------------------------------------------------------------------------
// getStartBalance
// retrieves the starting value of an account
int LOSEAccount::getStartBalance() const {

    //retrieve
    return startBalance;
}

//----------------------------------------------------------------------------
// getCurrentBalance
// retrieves the current value of an account
int LOSEAccount::getCurrentBalance() const {

    //retrieve
    return startBalance;
}

//----------------------------------------------------------------------------
// isBalanceZero
// checks if current balance is empty
bool LOSEAccount::isBalanceZero() const {

    //check for a zero balance
    if (currentBalance == 0) {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// assignment operator
// returns a copy of the LOSEAccount object
LOSEAccount& LOSEAccount::operator=(const LOSEAccount& acc) {

    //check for negative values
    if (this->currentBalance < 0 || acc.currentBalance < 0) {
        //what can we do about this case?
    }

    LOSEAccount temp;

    //copies data over
    temp.setStartBalance(acc.currentBalance);
    temp.adjustBalance(acc.currentBalance);
    return temp;
}

//----------------------------------------------------------------------------
// operator<
// < defined by value of currentBalance
bool LOSEAccount::operator<(const LOSEAccount& acc) const {

    //compare value of currentBalance
    if (this->currentBalance < acc.currentBalance) {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// operator<=
// <= defined by value of currentBalance
bool LOSEAccount::operator<=(const LOSEAccount& acc) const {

    // compare value of currentBalance
    if (this->currentBalance <= acc.currentBalance) {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// operator>
// > defined by value of currentBalance
bool LOSEAccount::operator>(const LOSEAccount& acc) const {

    // compare value of currentBalance
    if (this->currentBalance > acc.currentBalance) {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// operator>=
// >= defined by value of currentBalance
bool LOSEAccount::operator>=(const LOSEAccount& acc) const {

    // compare value of currentBalance
    if (this->currentBalance >= acc.currentBalance) {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// operator==
// == defined by value of currentBalance
bool LOSEAccount::operator==(const LOSEAccount& acc) const {
    if (this->currentBalance == acc.currentBalance) {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// operator!=
// != defined by value of currentBalance
bool LOSEAccount::operator!=(const LOSEAccount& acc) const {

    if (this->currentBalance != acc.currentBalance) {
        return true;
    }
    return false;
}