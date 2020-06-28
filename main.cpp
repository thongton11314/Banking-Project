// Developer: Thong Ton, Max Trinh
// Assignment of class 342
// Professor: Carol Zander
#include <iostream>
#include "manager.h"

using namespace std;

// Project:
//  -- Software application to handle transactions for local financial firm 
//     called Lots Of Savings Earned (LOSE).
//  -- This software be able to display the contents of the firm 
//     at any time and to allow clients to perform transactions 
//     on their various accounts.
//  -- Process an arbitrary sequence of transactions 
//     (deposit, withdraw, move, history)
//       - Won't display a message for a correctly performed transaction.
//       - Do display error messages for incorrect transactions.
//  -- Display the firm information at the end of the day, 
//     including clients and their beginning and final balances
//     of all accounts.

// Main:
//
//  Assumption:
//   -- the text files "lab5data.txt" and "lab5command.txt" exist and
//      are not empty.
//   -- Manager class is locatable and functional.
//
//  Implementation:
//   -- buildClients opens the file given then retrieve clients from there.
//   -- buildTransactions opens the file given then retrieve transaction.
//      from there
//   -- processTransaction process transaction after build transaction.
//   -- report will show all report of clients initial and final balance.
//
//---------------------------------------------------------------------------
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
    
    //display client history, report, or error message
    bank.report();
}