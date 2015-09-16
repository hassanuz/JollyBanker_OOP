/*Hassan Uraizee
Bank*/
#include "Transactions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


int main()
{
	Transactions Bank; 
	if(Bank.readFile("BankTransIn.txt"))
	{
		Bank.processTransactions();
		cout << "Processing Done. Final Balances" << endl;
		Bank.Display();
	}
	else {
		cout << "File not found";
	}
	return 0;
}

