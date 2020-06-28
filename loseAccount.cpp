#include "loseAccount.h"

//----------------------------------------------------------------------------
// constructor
// initialize both balance zero
LOSEAccount::LOSEAccount() {
    initialBalance = finalBalance = 0;
}

//----------------------------------------------------------------------------
// destructor
// deallocate memory
LOSEAccount::~LOSEAccount() {}

//----------------------------------------------------------------------------
// setInitialBalance
// sets the initial value of an account
bool LOSEAccount::setInitialBalance(int val) {

    //controls for negative values
    if (val < 0) {
        initialBalance = finalBalance = 0;
        return false;
    }
    initialBalance = finalBalance = val;
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
int LOSEAccount::getInitialBalance() const {
    return initialBalance;
}

//----------------------------------------------------------------------------
// getCurrentBalance
// retrieves the current value of an account
int LOSEAccount::getFinalBalance() const {
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