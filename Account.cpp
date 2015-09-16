/*Hassan Uraizee*/
#include "Account.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


Account::Account()
{
	allFunds[0].setFundName("Money Market");
	allFunds[1].setFundName("Prime Money Market");
	allFunds[2].setFundName("Long-Term Bond");
	allFunds[3].setFundName("Short-Term Bond");
	allFunds[4].setFundName("500 Index Fund");
	allFunds[5].setFundName("Capital Value Fund");
	allFunds[6].setFundName("Growth Equity Fund");
	allFunds[7].setFundName("Growth Index Fund");
	allFunds[8].setFundName("Value Fund");
	allFunds[9].setFundName("Value Stock Index");
}
Account::~Account()
{

}

string Account::getFundName(int fundID)
{
	return allFunds[fundID].getFundName();
}

Fund Account::getFundbyID(int fundID)
{
	return allFunds[fundID];
}

void Account::displayFunds()
{

	for (int i = 0; i < 10; i++)
	{
		cout << allFunds[i];
	}
}

void Account::writeToFund(int fundID, string text)
{
	allFunds[fundID].addToHistory(text);
}

void Account::displayHistoryFund(int fundID)
{
	allFunds[fundID].printHistory();
}

void Account::setFirstName(string firstName)
{
	this->firstName = firstName;
}
void Account::setLastName(string lastName)
{
	this->lastName = lastName;
}
void Account::setID(int ID)
{
	this->ID = ID;
}

string Account::getFirstName() const
{
	return firstName;
}
string Account::getLastName() const
{
	return lastName;
}
int Account::getID() const
{
	return ID;
}
int Account::getTotalBalance() const
{
	return totalBalance;
}

bool Account::getError() const
{
	return error;
}
void Account::setError(bool input)
{
	error = input;
}

void Account::Add(int amount)
{
	totalBalance += amount;
}


void Account::readFile(string fileName)
{
	string line;
	ifstream inFile;
	inFile.open(fileName);

	if (inFile)
	{
		while (getline(inFile, line))
		{
			transactions.push(line);
		}
		inFile.close();
	}

}

void Account::addToFund(int fund, int amount)
{
	allFunds[fund].add(amount);
}

void Account::withdrawFromFund(int fund, int amount, bool &otherFund, int &diff)
{
	otherFund = true;
	diff = allFunds[fund].getBalance();
	if (allFunds[fund].getBalance() < amount)
	{

		if (((allFunds[0].getBalance() < amount) && (allFunds[0].getBalance() + allFunds[1].getBalance() >= amount)) && (fund == 0))
		{
			int temp = allFunds[0].getBalance();
			allFunds[0].setBalance(0);
			amount -= temp;
			allFunds[1].setBalance(allFunds[1].getBalance() - amount);
		}

		else if (((allFunds[1].getBalance() < amount) && (allFunds[0].getBalance() + allFunds[1].getBalance() >= amount)) && (fund == 1))
		{
			int temp = allFunds[1].getBalance();
			allFunds[1].setBalance(0);
			amount -= temp;
			allFunds[0].setBalance(allFunds[0].getBalance() - amount);
		}

		else if (((allFunds[2].getBalance() < amount) && (allFunds[2].getBalance() + allFunds[3].getBalance() >= amount)) && (fund == 2))
		{
			int temp = allFunds[2].getBalance();
			allFunds[2].setBalance(0);
			amount -= temp;
			allFunds[3].setBalance(allFunds[3].getBalance() - amount);
		}

		else if (((allFunds[3].getBalance() < amount) && (allFunds[2].getBalance() + allFunds[3].getBalance() >= amount)) && (fund == 3))
		{
			int temp = allFunds[3].getBalance();
			allFunds[3].setBalance(0);
			amount -= temp;
			allFunds[2].setBalance(allFunds[2].getBalance() - amount);
		}
		else
		{
			error = true;
			otherFund = false;
			cerr << "ERROR: Not enough funds to withdraw " << amount << " from ";
		}


	}
	else
	{
		otherFund = false;
		allFunds[fund].subtract(amount);
	}


}

ostream& operator<< (ostream &outStream, const Account &acc)
{
	outStream << acc.getFirstName() << " " << acc.getLastName() << " Account ID: " << acc.getID();
	return outStream;
}








