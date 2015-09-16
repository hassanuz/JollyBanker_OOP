
/*Hassan Uraizee*/

#include "Fund.h"
#include <iostream>
using namespace std;

Fund::Fund()
{
	balance = 0;
}
Fund::Fund(string name)
{
	fundName = name;
}
Fund::~Fund()
{

}

void Fund::setFundName(string name)
{
	fundName = name;
}
string Fund::getFundName() const
{
	return fundName;
}

int Fund::getBalance() const
{
	return balance;
}

void Fund::setBalance(int balance)
{
	this->balance = balance;
}
void Fund::printHistory()
{
	{
		for (int i = 0; i < history.size(); i++)
		{
			cout << history[i] << endl;
		}
	}
}

int Fund::historySize()
{
	return history.size();	
}
void Fund::addToHistory(string text)
{
	history.push_back(text);
}

void Fund::add(int amount)
{
	balance += amount;
}

void Fund::subtract(int amount)
{
	balance -= amount;
	if (balance < 0)
	{
		cerr << "ERROR: Cannot have negative balance" << endl;

	}
}

ostream& operator<< (ostream &outStream, const Fund &fund)
{
	outStream << fund.getFundName() << ": $" << fund.getBalance() << endl;
	return outStream;
}