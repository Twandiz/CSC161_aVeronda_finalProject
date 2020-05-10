#include "drink.h"
// que implementation

// TODO: add timed drink pop, should be implemented in main

template <class T>
drink<T>::drink()
{
	
	front = nullptr;
	rear = nullptr;
	numDrinks = 0;
}

template <class T>
drink<T>::~drink()
{

	clear();
}

// adds drink to que
template <class T>
void drink<T>::addDrink( Beer::BeerObj search)
{
	
	DrinkQueNode* newNode = nullptr;
	newNode = new DrinkQueNode;
	
	
	if (BinaryTreeDrinks::searchNode(search))
	{
		Beer temp;
		temp = searchDB(search);
		newNode->beerQueObject = temp;

		newNode->next = nullptr;

		if (isEmpty())
		{
			front = rear = newNode;
		}
		else
		{
			rear->next = newNode;
			rear = newNode;
		}

		//writeToFileCurrentSession(temp);
		numDrinks++;
	}
}

// should be time limited in main
// returns -1 if empty, removes drink form que otherwise
template <class T>
int drink<T>::removeDrink( DrinkQueNode* popDrink)
{
	DrinkQueNode* temp = nullptr;

	if (isEmpty())
		return -1;
	else
	{
		//call write function from drinkStack
		popDrink->beerQueObject = front->beerQueObject;
		
		temp = front->next;
		delete front;
		front = temp;
		numDrinks--;

		return 0;
	}
}

template <class T>
bool drink<T>::isEmpty()
{
	bool status = true;

	if (numDrinks)
	{
		status = false;
	}

	return status;
}

template <class T>
void drink<T>::clear()
{
	DrinkQueNode* value{}; // dummy value

	while (!isEmpty())
	{
		removeDrink(value);
	}
}


