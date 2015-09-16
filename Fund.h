/*Hassan Uraizee*/

#ifndef FUND_H
#define FUND_H

#include <stdio.h>
#include <string> 
#include <vector>
#include <iostream> 
using namespace std;

class Fund
{
	friend ostream& operator<< (ostream &outStream, const Fund &fund);
public:
	Fund();
	Fund(string name);
	~Fund();
	void setFundName(string name);
	string getFundName() const;
	int getBalance() const;
	void setBalance(int balance);
	void add(int amount);
	void subtract(int amount);
	void printHistory();
	void addToHistory(string text);
	int historySize();

private:
	string fundName;
	int balance;
	vector<string> history;

};

#endif