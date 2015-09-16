/*Hassan Uraizee*/

#include "Transactions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


bool Transactions::readFile(string fileName)
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
		return true;
	}
}

void Transactions::Open(string firstName, string lastName, int ID)
{
	Account *temp;
	accounts.Retrieve(ID, temp);
	if (temp == NULL)
	{

		Account *newAccount = new Account();
		newAccount->setLastName(lastName);
		newAccount->setFirstName(firstName);
		newAccount->setID(ID);
		accounts.Insert(newAccount);

	}
	else
	{
		cerr << "ERROR: Account " << ID << " is already open. Transaction refused" << endl;
	}
}

void Transactions::Deposit(int ID, int fundID, int amount, bool transferred)
{

	Account *insAccount;

	accounts.Retrieve(ID, insAccount);

	if (insAccount != NULL)
	{
		insAccount->addToFund(fundID, amount);
	}
	else
	{
		cerr << "ERROR: Account " << ID << " not found. Deposit refused" << endl;
		return;
	}

	string input;
	ostringstream convert;
	convert << ID << fundID << " " << amount;
	input = convert.str();

	if (transferred == false)
	{
		string allText = "D " + input;
		insAccount->writeToFund(fundID, allText);
	}
}

bool Transactions::Withdraw(int ID, int fundID, int amount, bool transferred, int &neg)
{

	bool otherFund = false;
	int difference = 0;
	Account *toWithdraw;
	accounts.Retrieve(ID, toWithdraw);
	bool result = true;

	if (toWithdraw != NULL && neg >= 0)
	{
		toWithdraw->withdrawFromFund(fundID, amount, otherFund, difference);
	}
	else if (neg < 0)
	{
		result = true;
	}
	else
	{
		cerr << "ERROR: Account " << ID << " not found. Withdrawal refused" << endl;
		return false;
	}

	string input;
	ostringstream convert;
	if (otherFund == true){
		convert << ID << fundID << " " << difference;
		neg = amount - difference;
	}
	else{
		convert << ID << fundID << " " << amount;
	}
	
	input = convert.str();
	string theError;
	if (toWithdraw->getError())
	{
		string message = toWithdraw->getFirstName() + " " + toWithdraw->getLastName() + " " + toWithdraw->getFundName(fundID);

		cout << message << endl;
		theError = " (Failed)";
		result = false;
	}

	if (transferred == false)
	{
		string allText = "W " + input + theError;
		toWithdraw->writeToFund(fundID, allText);
	}

	return result;
}

void Transactions::Transfer(int ID, int fundID, int amount, int transferID, int transferFundID)
{

	Account *first;
	Account *second;
	int x = 0;
	accounts.Retrieve(ID, first);
	accounts.Retrieve(transferID, second);
	bool wasTransferred;
	if (first != NULL && second != NULL)
	{

		if (Withdraw(ID, fundID, amount, true, x))
		{
			Deposit(transferID, transferFundID, amount, true);
			wasTransferred = true;
		}
	}
	else
	{
		if (first == NULL)
		{
			cerr << "ERROR: Account " << ID << " does not exist. Transferal refused" << endl;
			return;
		}
		else
		{
			cerr << "ERROR: Account " << transferID << " does not exist. Transferal refused" << endl;
			return;
		}
	}

	string input;
	ostringstream convert;
	convert << "T " << ID << fundID << " " << amount << " " << transferID << transferFundID;
	input = convert.str();
	string allText = input;
	if (wasTransferred == false)
	{
		allText += " (Failed)";
	}

	first->writeToFund(fundID, allText);
	second->writeToFund(transferFundID, allText);


}

void Transactions::displayHistory(int ID)
{
	Account *temp;

	accounts.Retrieve(ID, temp);

	cout << "Transaction History for " << temp->getFirstName() + " " + temp->getLastName() << " by fund." << endl;

	for (int i = 0; i < 10; i++)
	{
		if (temp->getFundbyID(i).historySize() > 0)
		{
			cout << temp->getFundbyID(i);
			temp->displayHistoryFund(i);
		}
		
	
	}
	cout << endl;

}
void Transactions::displayHistory(int ID, int fundID)
{
	Account *temp;
	accounts.Retrieve(ID, temp);
	string name = temp->getFirstName() + " " + temp->getLastName();
	cout << "Transaction History for " << name << " " << temp->getFundbyID(fundID);
	temp->displayHistoryFund(fundID);
}

void Transactions::processTransactions()
{

	while (!transactions.empty())
	{
		string line = transactions.front();
		string command = line.substr(0, 1);
		string stringWOCommand = line.substr(2, line.length());

		if (command == "O")
		{

			string lastNameWString = line.substr(2, line.length());
			string theLastName = lastNameWString.substr(0, lastNameWString.find(" "));

			string firstNameWString = lastNameWString.substr(lastNameWString.find(" ") + 1, lastNameWString.length());
			string theFirstName = firstNameWString.substr(0, firstNameWString.find(" "));

			string accountNum = firstNameWString.substr(firstNameWString.find(" ") + 1, firstNameWString.length());
			int theID = atoi(accountNum.c_str());

			Open(theFirstName, theLastName, theID);


		}

		if (command == "D")
		{
			string theID = line.substr(2, 4);
			string fund = line.substr(6, 1);
			string theAmount = line.substr(8);
			int ID = atoi(theID.c_str());
			int fundID = atoi(fund.c_str());
			int amount = atoi(theAmount.c_str());


			Deposit(ID, fundID, amount, false);

		}

		if (command == "W")
		{
			int neg = 0;
			string theID = line.substr(2, 4);
			string fund = line.substr(6, 1);
			string theAmount = line.substr(8);
			int ID = atoi(theID.c_str());
			int fundID = atoi(fund.c_str());
			int amount = atoi(theAmount.c_str());

			Withdraw(ID, fundID, amount, false, neg);
			if (fundID == 2 && neg > 0){
				amount = neg;
				neg = -1;
				Withdraw(ID, 3, amount, false, neg);
			}
			 else if (fundID == 0 && neg > 0){
				amount = neg;
				neg = -1;
				Withdraw(ID, 1, amount, false, neg);
			}
			 else if (fundID == 1 && neg > 0){
				 amount = neg;
				 neg = -1;
				 Withdraw(ID, 0, amount, false, neg);
			 }
			 else if (fundID == 3 && neg > 0){
				 amount = neg;
				 neg = -1;
				 Withdraw(ID, 2, amount, false, neg);
			 }


		}
		if (command == "T")
		{
			string theID = line.substr(2, 4);
			string fund = line.substr(6, 1);
			string lineWOCommand = line.substr(line.find(" ") + 1, line.length());

			string amountWString = lineWOCommand.substr(lineWOCommand.find(" ") + 1, lineWOCommand.length());
			string finalAmount = amountWString.substr(0, amountWString.find(" "));

			string theTransferID = amountWString.substr(amountWString.find(" ") + 1, 4);
			string thefundID = amountWString.substr(amountWString.length() - 1, 1);
			int ID = atoi(theID.c_str());
			int fundID = atoi(fund.c_str());
			int amount = atoi(finalAmount.c_str());


			int transferID = atoi(theTransferID.c_str());
			int transferFund = atoi(thefundID.c_str());


			Transfer(ID, fundID, amount, transferID, transferFund);

		}

		if (command == "H")
		{
			string theID = line.substr(2);
			if (theID.length() > 4)
			{

				string theFundID = theID.substr(4);
				string realID = theID.substr(0, 4);
				int ID = atoi(realID.c_str());
				int fundID = atoi(theFundID.c_str());

				displayHistory(ID, fundID);
			}
			else
			{
				int ID = atoi(theID.c_str());
				displayHistory(ID);

			}

		}
		transactions.pop();
	}
}

void Transactions::Display()
{
	accounts.Display();

}
