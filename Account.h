/*Hassan Uraizee*/

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <stdio.h>
#include <string>
#include <queue>
#include <vector>
#include "Fund.h"
using namespace std;

class Account
{
	friend ostream& operator<< (ostream &outStream, const Account &acc);
public:
	Account();
	~Account();
	Account(string firstName, string lastName, int ID);
	string getFirstName() const;
	string getLastName() const;
	string getFundName(int fundID);
	Fund getFundbyID(int fundID);
	int getID() const;
	int getTotalBalance() const;
	void setFirstName(string firstName);
	void setLastName(string lastName);
	void setID(int ID);
	bool getError() const;
	void setError(bool input);
	void Add(int amount);
	void readFile(string fileName);
	void processTransactions();
	void processFunds();
	void displayFunds();
	void addToFund(int fund, int amount);
	void withdrawFromFund(int fund, int amount, bool &more , int &diff);
	void writeToFund(int fundID, string text);
	void displayHistoryFund(int fundID);
private:
	string firstName;
	string lastName;
	string trans;
	int ID;
	int fundID;
	int totalBalance;
	int funds[10];
	bool error;
	queue<string> transactions;
	Fund allFunds[10];

};
#endif

