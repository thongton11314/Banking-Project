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
    ~LOSEAccount();
    bool setStartBalance(int);       // set start ballance
    bool adjustBalance(int);         // use for adjust current balance
    int getStartBalance() const;     // get start balance
    int getFinalBalance() const;   // return balance of the account
    bool isBalanceZero() const;      // check if the account has no money

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
    int startBalance;
    int finalBalance;
};

#endif // !_LOSE_ACCOUNT_s
