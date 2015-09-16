/*Hassan Uraizee*/

#include "BSTree.h"
#include <iostream>
using namespace std;

BSTree::BSTree()
{
	root = NULL;
}
BSTree::~BSTree()
{
	Empty();
}

bool BSTree::Insert(Account *toInsert)
{
	Node *insNode = new Node;
	insNode->pAcct = toInsert;
	insNode->left = NULL;
	insNode->right = NULL;
	if (root == NULL)
	{
		root = insNode;
		return true;
	}
	Insert(root, toInsert);
	return true;
}

void BSTree::Insert(Node *cur, Account *toInsert)
{
	Node *insNode = new Node;
	insNode->left = NULL;
	insNode->right = NULL;
	insNode->pAcct = toInsert;
	if (cur == NULL)
	{
		cur = insNode;
		return;
	}
	else if (toInsert->getID() < cur->pAcct->getID())
	{
		if (cur->left == NULL)
		{
			cur->left = insNode;
		}
		else
		{
			Insert(cur->left, toInsert);
		}
	}
	else
	{
		if (cur->right == NULL)
		{
			cur->right = insNode;
		}
		else
		{
			Insert(cur->right, toInsert);
		}
	}
}

bool BSTree::Retrieve(int target, Account * &ptrRetrieve) const
{
	ptrRetrieve = Retrieve(root, target);
	return ptrRetrieve != NULL;

}

Account * BSTree::Retrieve(Node *cur, int targetID) const
{
	if (cur == NULL)
	{
		return NULL;

	}
	else if (cur->pAcct->getID() == targetID)
	{
		return cur->pAcct;

	}
	else if (targetID < cur->pAcct->getID())
	{
		return Retrieve(cur->left, targetID);
	}
	else
	{
		return Retrieve(cur->right, targetID);
	}
}



void BSTree::Display() const
{
	Display(root);
}

void BSTree::Display(Node *cur) const
{
	if (cur == NULL)
	{
		return;
	}
	Display(cur->left);
	cout << *cur->pAcct << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << cur->pAcct->getFundbyID(i);
	}
	cout << endl;
	Display(cur->right);
}

void BSTree::Empty(Node *cur)
{
	if (cur == NULL)
	{
		return;
	}
	else if (cur->left != NULL)
	{
		Empty(cur->left);
	}
	else if (cur->right != NULL)
	{
		Empty(cur->right);
	}
	else if (cur != NULL)
	{
		delete cur->pAcct;
		delete cur;
		cur = NULL;
	}
}
void BSTree::Empty()
{
	Empty(root);

}
bool BSTree::isEmpty() const
{
	return root == NULL;
}