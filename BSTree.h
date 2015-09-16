/*Hassan Uraizee*/
#ifndef BSTree_H
#define BSTree_H


#include <stdio.h>
#include "Account.h"


class BSTree
{
	struct Node
	{
		Account *pAcct;
		Node *right;
		Node *left;
	};
private:
	void Insert(Node *cur, Account *toInsert);
	Account * Retrieve(Node *cur, int targetID) const;
	void Empty(Node *cur);
	void Display(Node *cur) const;
	Node *root;
public:
	BSTree();
	~BSTree();
	bool Insert(Account *toInsert);
	bool Retrieve(int ID, Account * &ptrRetrieve) const;
	void Display() const;
	void Empty();
	bool isEmpty() const;
};
#endif