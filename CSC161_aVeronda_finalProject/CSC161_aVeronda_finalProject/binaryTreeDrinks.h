#pragma once

// Binary tree function, butchered to hell and back


//TODO: Remove cout statements, should return checks 

#include "Beer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <exception>

using namespace std;


template <class T>
class BinaryTreeDrinks
{
public:
	friend class Beer;
	struct DrinkNode
	{
		Beer beerTreeObject;
		DrinkNode* left;
		DrinkNode* right;
	};

	DrinkNode* root;
	void insert(DrinkNode*&, DrinkNode*&);
	void destroySubTree(DrinkNode*);
	void deleteNode(T, DrinkNode*&);
	void makeDeletion(DrinkNode*&);
	void displayInOrder(DrinkNode*);
	void populateTree();

public:
	BinaryTreeDrinks() //constructor
	{
		root = nullptr;
		populateTree();
	}
	~BinaryTreeDrinks() // destructor
	{
		destroySubTree(root);
	}

	void insertNode(Beer&);
	bool searchNode(T);
	void remove(T); // left in as posible way to delete drinks
	void displayInOrder()
	{
		displayInOrder(root);
	}
	T returnValue(T);

	T* operator =(const T& other) 
	{
		return *other;
	}

	

	
};

//*******************************************************************
// insert accepts a treenodepointer and a pointer to a node. The Function
// inserts the node into the tree pointed to by the treenode pointer. 
// This function is called recursively
//*******************************************************************

template <class T>
void BinaryTreeDrinks<T>::insert(DrinkNode*& nodePtr, DrinkNode*& newNode)
{
	if (nodePtr == nullptr)
	{
		nodePtr = newNode; // inserts node
	}
	else if (newNode->beerTreeObject < nodePtr->beerTreeObject)
	{
		insert(nodePtr->left, newNode); // search left branch
	}
	else
	{
		insert(nodePtr->right, newNode); // search right branch
	}
}

//**********************************************************************
// insertNode creates a new node to hold num as its value,
// and passes it to the insert function.
//**********************************************************************

template <class T>
void BinaryTreeDrinks<T>::insertNode(Beer& num) // intellisense error, over my head right now, has to do with declaration order, will compile
{
	DrinkNode* newNode = nullptr; // point to a new node

	// create a new node and store num in it
	newNode = new DrinkNode;
	newNode->beerTreeObject = num;
	newNode->left = newNode->right = nullptr;

	//insert the node
	insert(root, newNode);

}

//**********************************************************************
// destroySubTree is called by the destructor. it deletes all nodes in the tree
//**********************************************************************

template <class T>
void BinaryTreeDrinks<T>::destroySubTree(DrinkNode* nodeptr)
{
	if (nodeptr->left)
	{
		destroySubTree(nodeptr->left);
	}
	if (nodeptr->right)
	{
		destroySubTree(nodeptr->right);
	}

	delete nodeptr;
}

//**********************************************************************
// searchNode determines if a value is present in the tree. 
// search in main requires something to add drink type to front of search  format: ^ = beer, & = wine, % = liquor
//**********************************************************************

template <class T>
bool BinaryTreeDrinks<T>::searchNode(T num)
{
	DrinkNode* drinkName = nullptr;
	bool found = false;
	DrinkNode* nodePtr = root;

	while (nodePtr)
	{
		if (nodePtr->beerTreeObject == num)
		{
			found = true;
			break;
		}
		else if (num < nodePtr->beerTreeObject)
		{
			nodePtr = nodePtr->left;
		}
		else
		{
			nodePtr = nodePtr->right;
		}
	}

	return found;
}

//**********************************************************************
// remove calls deleteNode to delete the node whose value member is the same as num
//**********************************************************************

template <class T>
void BinaryTreeDrinks<T>::remove(T num)
{
	deleteNode(num, root);
}

template<class T>
inline T BinaryTreeDrinks<T>::returnValue(T searchFor)
{
	searchNode(searchFor);


	return T;
}

template <class T>
void BinaryTreeDrinks<T>::deleteNode(T num, DrinkNode*& nodePtr)
{
	if (num < nodePtr->value)
	{
		deleteNode(num, nodePtr->left);
	}
	else if (num > nodePtr->value)
	{
		deleteNode(num, nodePtr->right);
	}
	else
	{
		makeDeletion(nodePtr);
	}
}

//**********************************************************************
// makeDeletion takes a reference to a pointer to the node that is to be 
// deleted. The node is removed and the branches of the tree below the node
// are reattached.
//**********************************************************************

template <class T>
void BinaryTreeDrinks<T>::makeDeletion(DrinkNode*& nodePtr)
{
	// Temporary pointer, used in reattaching the left subtree
	DrinkNode* tempNodePtr = nullptr;

	if (nodePtr == nullptr)
	{
		cout << "Cannot delete empty node.\n"; 
	}
	else if (nodePtr->right == nullptr)
	{
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left;
		delete tempNodePtr;
	}
	else if (nodePtr->left == nullptr)
	{
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	}
	// if the node has two children
	else
	{
		// move one node to the right
		tempNodePtr = nodePtr->right;

		// go to the end of the left node
		while (tempNodePtr->left)
		{
			tempNodePtr = tempNodePtr->left;
		}

		// reattach the left subtree
		tempNodePtr->left = nodePtr->left;
		tempNodePtr = nodePtr;

		//reattach the right subtree
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	}
}

//**********************************************************************
// The displayInOrder member function displays the values in the subtree
// pointed to by nodePtr, via inroder traversal
//**********************************************************************

template <class T>
void BinaryTreeDrinks<T>::displayInOrder(DrinkNode* nodePtr)
{
	if (nodePtr)
	{
		displayInOrder(nodePtr->left);
		cout << nodePtr->beerTreeObject << endl;
		displayInOrder(nodePtr->right);
	}
}


// might move into main, only calls insert(), included in constructor
template<class T>
void BinaryTreeDrinks<T>::populateTree()
{
	ifstream inFile;
	inFile.open("drinkDB.txt");
	int count = 0;
	char getDBEntry[100];
	typename Beer::Beer beerInfo;

	

	if (inFile)
	{
		inFile.ignore(1000, '!');

		while (!inFile.eof()) // could be .eof() not sure of included checks in .good()
		{
			
			inFile.getline(getDBEntry, 256, '_');
			beerInfo.abv = stod(getDBEntry);
			
			inFile.getline(getDBEntry, 256, '_');
			beerInfo.name = getDBEntry;
			
			inFile.getline(getDBEntry, 256, '_');
			beerInfo.type = getDBEntry;

			inFile.getline(getDBEntry, 256, '_');
			beerInfo.hoppiness = stoi(getDBEntry);

			inFile.getline(getDBEntry, 256, '_');
			beerInfo.darkness = stoi(getDBEntry);
			//getDBEntry.clear();

			inFile.getline(getDBEntry, 256, '_');
			beerInfo.producer = getDBEntry;
			//getDBEntry.clear();

			inFile.getline(getDBEntry, 256, '_');
			beerInfo.microBrew = stoi(getDBEntry);
			//getDBEntry.clear();

			inFile.getline(getDBEntry, 256, '_');
			beerInfo.drankPreviously = stoi(getDBEntry);
			//getDBEntry.clear();

			inFile.getline(getDBEntry, 256, '_');
			beerInfo.likedDrink = stoi(getDBEntry);
			

			insertNode(beerInfo);
			
			try
			{
				inFile.peek();
			}
			catch (const std::exception& e)
			{
				break;
			}
		}
		
		inFile.close();
	}
	else
	{
		cout << "something went wrong"; // don't like this
	}
	
}
