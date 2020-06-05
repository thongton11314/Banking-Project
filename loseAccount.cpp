#include "loseAccount.h"

LOSEAccount::LOSEAccount() {
    finalBalance = 0;
    startBalance = 0;
}

LOSEAccount::~LOSEAccount() {}

bool LOSEAccount::setStartBalance(int val) {

    //controls for negative values
    if (val < 0) {
        startBalance = finalBalance = 0;
        return false;
    }
    startBalance = finalBalance = val;
    return true;
}

bool LOSEAccount::adjustBalance(int val) {

    //controls for negative output
    if ((finalBalance + val) < 0) {
        return false;
    }
    finalBalance += val;
    return true;
}


int LOSEAccount::getStartBalance() const {

    //retrieve
    return startBalance;
}


int LOSEAccount::getFinalBalance() const {
    return finalBalance;
}

bool LOSEAccount::isBalanceZero() const {

    if (finalBalance == 0) {
        return true;
    }
    return false;
}

LOSEAccount& LOSEAccount::operator=(const LOSEAccount& acc) {
    this->startBalance = acc.startBalance;
    this->finalBalance = acc.finalBalance;
    return *this;
}

bool LOSEAccount::operator<(const LOSEAccount& acc) const {
    if (this->finalBalance < acc.finalBalance) {
        return true;
    }
    return false;
}

bool LOSEAccount::operator<=(const LOSEAccount& acc) const {

    // compare value of currentBalance
    if (this->finalBalance <= acc.finalBalance) {
        return true;
    }
    return false;
}

bool LOSEAccount::operator>(const LOSEAccount& acc) const {

    // compare value of currentBalance
    if (this->finalBalance > acc.finalBalance) {
        return true;
    }
    return false;
}

bool LOSEAccount::operator>=(const LOSEAccount& acc) const {
    if (this->finalBalance >= acc.finalBalance) {
        return true;
    }
    return false;
}

bool LOSEAccount::operator==(const LOSEAccount& acc) const {
    if (this->finalBalance == acc.finalBalance) {
        return true;
    }
    return false;
}

bool LOSEAccount::operator!=(const LOSEAccount& acc) const {

    if (this->finalBalance != acc.finalBalance) {
        return true;
    }
    return false;
}
