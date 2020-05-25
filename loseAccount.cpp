#include "loseAccount.h"

//----------------------------------------------------------------------------
// constructor
// constructs things
LOSEAccount::LOSEAccount() {
    finalBalance = 0;
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
        startBalance = finalBalance = 0;
        return false;
    }
    startBalance = finalBalance = val;
    return true;
}

//----------------------------------------------------------------------------
// adjustBalance
// adjusts the currentBalance value
bool LOSEAccount::adjustBalance(int val) {

    //controls for negative output
    if ((finalBalance + val) < 0) {
        return false;
    }
    finalBalance += val;
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
int LOSEAccount::getFinalBalance() const {

    //retrieve
    return finalBalance;
}

//----------------------------------------------------------------------------
// isBalanceZero
// checks if current balance is empty
bool LOSEAccount::isBalanceZero() const {

    //check for a zero balance
    if (finalBalance == 0) {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// assignment operator
// returns a copy of the LOSEAccount object
LOSEAccount& LOSEAccount::operator=(const LOSEAccount& acc) {

    // assign other account into current account
    this->startBalance = acc.startBalance;
    this->finalBalance = acc.finalBalance;
    return *this;
}

//----------------------------------------------------------------------------
// operator<
// < defined by value of currentBalance
bool LOSEAccount::operator<(const LOSEAccount& acc) const {

    //compare value of currentBalance
    if (this->finalBalance < acc.finalBalance) {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// operator<=
// <= defined by value of currentBalance
bool LOSEAccount::operator<=(const LOSEAccount& acc) const {

    // compare value of currentBalance
    if (this->finalBalance <= acc.finalBalance) {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// operator>
// > defined by value of currentBalance
bool LOSEAccount::operator>(const LOSEAccount& acc) const {

    // compare value of currentBalance
    if (this->finalBalance > acc.finalBalance) {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// operator>=
// >= defined by value of currentBalance
bool LOSEAccount::operator>=(const LOSEAccount& acc) const {

    // compare value of currentBalance
    if (this->finalBalance >= acc.finalBalance) {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// operator==
// == defined by value of currentBalance
bool LOSEAccount::operator==(const LOSEAccount& acc) const {
    if (this->finalBalance == acc.finalBalance) {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// operator!=
// != defined by value of currentBalance
bool LOSEAccount::operator!=(const LOSEAccount& acc) const {

    if (this->finalBalance != acc.finalBalance) {
        return true;
    }
    return false;
}