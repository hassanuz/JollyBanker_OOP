/*Hassan Uraizee*/
#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <stdio.h>
#include <string>
#include <queue>
#include "BSTree.h"
#include "Account.h"
using namespace std;

class Transactions
{
public:
	bool readFile(string fileName);
	void processTransactions();
	void Open(string firstName, string lastName, int ID);
	void Deposit(int ID, int fundID, int amount, bool transferred);
	bool Withdraw(int ID, int fundID, int amount, bool transferred, int& negbalance);
	void Transfer(int ID, int fundID, int amount, int transferID, int transferFundID);
	void displayHistory(int ID);
	void displayHistory(int ID, int fundID);
	void Display();
private:
	BSTree accounts;
	queue<string> transactions;

};
#endif