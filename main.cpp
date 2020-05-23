#include <iostream>
#include "manager.h"

using namespace std;

//---------------------------------------------------------------------------
// Main
int main() {

    // instantiate manager class
    Manager bank;

    // instantiate file stream for setting data
    ifstream clientFile("lab5data.txt"), 
        transactionFile("lab5command.txt");
    
    // reads all client information from text file
    bank.buildClients(clientFile);

    // reads all client command from text file
    bank.buildTransactions(transactionFile);

    // process all transaction from file
    bank.processTransactions();

    //display history of client
    bank.displayReport();
}