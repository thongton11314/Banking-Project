#pragma once
#ifndef LOSE_ACCOUNT
#define LOSE_ACCOUNT

//---------------------------------------------------------------------------
// LOSEAccount class:  
//   -- Holds the balance of the account.
//   -- Sets own balance and returns it.
//
// Assumptions:
//   -- Balance never be negative.
//   -- LOSEAccount object will be instanced in client object.
//   -- Handle any function will be perform by client object.
// 
// Implementation:
//  -- start balance is the balance before any transaction.
//  -- end balance is the balance after performing any transaction.
//---------------------------------------------------------------------------

class LOSEAccount {

public:
    LOSEAccount();                   // constructor
    ~LOSEAccount();                  // destructor
    bool setInitialBalance(int);     // set start ballance
    bool adjustBalance(int);         // use for adjust final balance
    int getInitialBalance() const;   // get start balance
    int getFinalBalance() const;     // return balance of the account
    bool isBalanceZero() const;      // check if the account has no money

private:
    int initialBalance;              // never changes after instance
    int finalBalance;                // updates every sucessful transaction
};
#endif // !LOSE_ACCOUNT