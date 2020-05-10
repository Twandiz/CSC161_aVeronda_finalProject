#pragma once

#include "Beer.h"
#include "BeerDataBase.h"
#include "binaryTreeDrinks.h"
#include "drinkStack.h"
#include <string>
#include <fstream>
#include <deque>
#include <iostream>



using namespace std;

// Que, takes in drinks, standard implemantation, uses currentSession.txt and binaryTreeDrinks.h

template <class T>
class drink
{
private:
	struct DrinkQueNode
	{
		T beerQueObject;
		DrinkQueNode* next;
	};
	DrinkQueNode* front;
	DrinkQueNode* rear;
	int numDrinks;


public:
	drink();
	~drink(); // TODO: write to file using drinkStack
	void addDrink( T& ); // will include timer to pop drinks afte 1 hour
	int removeDrink( DrinkQueNode* ); // time based, implement in main call based on time
	bool isEmpty();
	void clear();
	void writeToFileCurrentSession(const T* currentDrink); // writes to currentsession.txt
	void writeToFileEndOfSession(const T* currentDrinkList); // never implemented, unfinished
	void saveSession();
	int size();
	T* getFront();
	T* getNext(DrinkQueNode*);
	
	friend ostream& operator<<(ostream& output, const DrinkQueNode& other)
	{
		output << other.name << '\n'
			<< "ABV: " << other.abv << '\n'
			<< "Hoppiness: " << other.hoppiness << '\n'
			<< "Dark Rating: " << other.darkness << '\n'
			<< "Producer: " << other.producer << '\n';

		return output;
	}
	//friend class BinaryTreeDrinks;

};


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
void drink<T>::addDrink(T& newDrink)
{

	DrinkQueNode* newNode = nullptr;
	newNode = new DrinkQueNode;

	newNode->beerQueObject = newDrink;

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

	

	writeToFileCurrentSession(&newDrink); // not object orriented approach
	numDrinks++;

}

// should be time limited in main
// returns -1 if empty, removes drink form que otherwise
template <class T>
int drink<T>::removeDrink(DrinkQueNode* popDrink)
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

template<class T>
void drink<T>::writeToFileCurrentSession(const T* currentDrink)
{
	ofstream outFile;
	if (numDrinks == 0)
	{
		outFile.open("currentSession.txt", std::ios_base::trunc);
		outFile << '%';
	}
	else
	{
		outFile.open("currentSession.txt", std::ios_base::app);
	}

	if (outFile)
	{
		outFile << currentDrink;
	}
	else
	{
		cout << "something went wrong"; // don't like this need try and catch, time
	}
	
	outFile.close();
}

template<class T>
void drink<T>::writeToFileEndOfSession(const T* currentDrinkList)
{
	ofstream outFile;
	outFile.open("previousSession.txt", std::ios_base::app);

	if (outFile)
	{
		for (int i = this.front; i < 0; i--)
		{
			//outFile << top();
			outFile << '\n';
			
		}

	}
	else
	{
		cout << "something went wrong"; // don't like this need try and catch, time
	}
	
	outFile.close();
}

template<class T>
inline int drink<T>::size()
{
	return this->numDrinks;
}


template<class T>
inline T* drink<T>::getFront()
{
	return front;
}

template<class T>
inline T* drink<T>::getNext(DrinkQueNode* current)
{
	return current->next;
}
