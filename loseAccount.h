#pragma once
#ifndef _LOSE_ACCOUNT_
#define _LOSE_ACCOUNT_

class LOSEAccount {

public:
    LOSEAccount();
    ~LOSEAccount();
    bool setStartBalance(int);       
    bool adjustBalance(int);    
    int getStartBalance() const;   
    int getFinalBalance() const;     
    bool isBalanceZero() const;  
    LOSEAccount& operator=(const LOSEAccount&);
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

#endif // !_LOSE_ACCOUNT_
