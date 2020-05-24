#include "transaction.h"

//----------------------------------------------------------------------------
// constructor
// constructs things
Transaction::Transaction() {
    
    //Nothing?
}

//----------------------------------------------------------------------------
// destructor
// used after each function to deallocate memory
Transaction::~Transaction() {

    //Nothing
}

//----------------------------------------------------------------------------
// copy constructor
// makes a perfect copy of the inputed Transaction object
Transaction::Transaction(const Transaction& other) {
    
    //copy all attributes over
    clientIDOne = other.clientIDOne;
    clientIDTwo = other.clientIDTwo;
    AccIDOne = other.AccIDOne;
    AccIDTwo = other.AccIDTwo;
    amount = other.amount;
    transType = other.transType;
}

//----------------------------------------------------------------------------
// setData
// sets all the values
bool Transaction::setData(ifstream& input) {

    //NOT DONE
}

//----------------------------------------------------------------------------
// getClientIDOne
// retrieves the ID of Client One
int Transaction::getClientIDOne() const {

    return clientIDOne;
}

//----------------------------------------------------------------------------
// getClientIDTwo
// retrieves the ID of Client Two
int Transaction::getClientIDTwo() const {
    
    return clientIDTwo;
}

//----------------------------------------------------------------------------
// getAccIDOne
// retrieves the account number
int Transaction::getAccIDOne() const {

    return AccIDOne;
}

//----------------------------------------------------------------------------
// getAccIDTwo
// retrieves the account number
int Transaction::getAccIDTwo() const {
    
    return AccIDTwo;
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

// ----------------------------------------------------------------------------
// assignment operator
// returns a copy of the Transaction object
Transaction& Transaction::operator=(const Transaction& trans) {
    
    //feed into copy constructor
    Transaction temp(trans);

    return temp; //compiler warning about *this?
}



