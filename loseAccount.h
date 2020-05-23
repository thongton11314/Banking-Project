#pragma once
#ifndef _LOSE_ACCOUNT_
#define _LOSE_ACCOUNT_

//---------------------------------------------------------------------------
// LOSEAccount class:  
//   -- holds the balance of the account
//   -- sets own balance and returns it
//
// Implementation and assumptions:
//   -- Balance never be negative
//
//---------------------------------------------------------------------------

class LOSEAccount {

public:
    LOSEAccount();
    void setStartBalance(int);       // set start ballance
    void adjustBalance(int);         // use for adjust current balance
    int getStartBlance() const;      // get start balance
    int getCurrentBalance() const;   // return balance of the account
    bool isBanlanceZero() const;     // check if the account has no money

    // copy operator
    LOSEAccount& operator=(const LOSEAccount&);

    // comparison operators 
    bool operator<(const LOSEAccount&) const;
    bool operator<=(const LOSEAccount&) const;
    bool operator>(const LOSEAccount&) const;
    bool operator>=(const LOSEAccount&) const;
    bool operator==(const LOSEAccount&) const;
    bool operator!=(const LOSEAccount&) const;

private:
    int currentBalance;
    int startBallance;
};

#endif // !_LOSE_ACCOUNT_

