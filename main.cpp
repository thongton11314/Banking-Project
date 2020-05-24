#include <iostream>
#include <assert.h>
#include "loseAccount.h"

using namespace std;
void testLOSEAccountClass();

int main() {
    testLOSEAccountClass();
}

void testLOSEAccountClass() {
    LOSEAccount account1;
    assert(account1.setStartBalance(100));
    assert(account1.isBalanceZero() != 0);
    assert(account1.getStartBalance() == 100);
    assert(account1.getCurrentBalance() == 100);
    assert(account1.adjustBalance(100) == true);
    assert(account1.adjustBalance(-500) == false);

    // Test operator
    LOSEAccount account2;
    assert(account2 < account1);
    assert(account2 <= account1);
    assert(account2 <= account2);
    assert(account1 > account2);
    assert(account1 >= account2);
    assert(account1 >= account1);
    assert(account2 != account1);
    assert(account2 == account2);
    cout << "Test LOSE account pass, end test." << endl;
}