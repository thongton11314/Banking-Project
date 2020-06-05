#pragma once
#ifndef _TRANSACTION_
#define _TRANSACTION_
#include <fstream>
#include <iomanip>

using namespace std;
class Transaction {
    friend ostream& operator<<(ostream &, const Transaction&);

public:
    Transaction();                   
    Transaction(const Transaction &);
    ~Transaction();              
    bool setData(ifstream&);       
    void setSufficient(bool);       
    void setUnknownClient(bool); 
    int getDeliveredClientID() const;
    int getReceivedClientID() const;
    int getDeliveredAccID() const; 
    int getReceivedAccID() const;
    char getTranType() const;
    int getAmount() const;
    bool isSufficient() const;
    bool isUnknownClient() const;

private:
    int deliveredClientID;
    int receivedClientID;
    int deliveredAccID;
    int receivedAccID;
    int amount; 
    bool sufficient;
    bool unknownClient;
    char transType;
};
#endif // !_TRANSACTION_
