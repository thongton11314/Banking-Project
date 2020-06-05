#include <iostream>
#include "manager.h"

using namespace std;

//---------------------------------------------------------------------------
// Main
int main() {
    Manager bank;
    ifstream clientFile("lab5data.txt"), 
        transactionFile("lab5command.txt");
    bank.buildClients(clientFile);
    bank.buildTransactions(transactionFile);
    bank.processTransactions();
    bank.report();
}
