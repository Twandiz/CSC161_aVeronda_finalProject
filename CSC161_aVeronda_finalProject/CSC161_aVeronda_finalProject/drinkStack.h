#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include "binaryTreeDrinks.h"

using namespace std;

// TODO: make stack size maliable (maybe vector)
//		get rid of cout statements
//		remove namespace std

template <class T> 
class drinkStack 
	: public BinaryTreeDrinks<T>
{
public:
	const drinkStack<T>& operator=(const drinkStack<T>&);
	// override the assigment operator

	void initializeStack();
	bool isEmptyStack() const;
	bool isFullStack() const;
	void push(const T& newItem);
	T top() const;
	void pop();
	drinkStack(int stackSize = 100);
	// constructor
	// create an array of the size stacksize to hold elements
	// the default size is 100, should be fine, will have to change for publish, maybe vector?
	drinkStack(const drinkStack<T>& otherStack);
	//copy constructor
	~drinkStack();
	// destructor, remove all elements of the stack
	bool operator==(const drinkStack<T>& otherStack) const;

	void writeToFileCurrentSession( const T* currentDrink);
	void writeToFileEndOfSession( const T* );


private:
	int maxStackSize;	// stores the max stack size
	int stackTop;		//points to the top of the stack
	T* list;			//pointer to the array that holds elements

	void copyStack(const drinkStack<T>& otherStack);
	// function to make a copy of other stack


};

template <class T>
void drinkStack<T>::initializeStack()
{
	stackTop = 0;
}

template <class T>
bool drinkStack<T>::isEmptyStack() const
{
	return (stackTop == 0);
}

template <class T>
bool drinkStack<T>::isFullStack() const
{
	return (stackTop == maxStackSize);
}

template <class T>
void drinkStack<T>::push( const T& newItem)
{
	if (!isFullStack())
	{
		list[stackTop] = newItem;
		stackTop++;
	}
	else
		cout << "Cannot add to a full stack." << endl;

}

template <class T>
T drinkStack<T>::top() const
{
	assert(stackTop != 0);

	return list[stackTop - 1];

}

template <class T>
void drinkStack<T>::pop()
{
	if (isEmptyStack())
	{
		stackTop--;

	}
	else
		cout << "Cannot remove frome an empty stack." << endl;
}

template <class T>
drinkStack<T>::drinkStack(int stackSize)
{
	if (stackSize <= 0)
	{
		cout << "Size of the array to hold the Stack must be positive" << endl;
		cout << "Creating an array of size 100." << endl;

		maxStackSize = 100;
	}
	else
	{
		maxStackSize = stackSize;
	}

	stackTop = 0;
	list = new T[maxStackSize];

}

template <class T>
drinkStack<T>::~drinkStack()
{
	
	delete[] list;
}

template <class T>
void drinkStack<T>::copyStack(const drinkStack<T>& otherStack)
{
	delete[] list;
	maxStackSize = otherStack.maxStackSize;
	stackTop = otherStack.stackTop;

	list = new T[maxStackSize];

	// copy other stack into this stack
	for (int j = 0; j < stackTop; j++)
	{
		list[j] = otherStack.list[j];
	}
}

template <class T>
drinkStack<T>::drinkStack(const drinkStack<T>& otherStack)
{
	list = nullptr;
	copyStack(otherStack);
}

template <class T>
const drinkStack<T>& drinkStack<T>::operator=(const drinkStack<T>& otherStack)
{
	if (this != &otherStack)
	{
		copyStack(otherStack);
	}

	return *this;
}

template <class T>
bool drinkStack<T>::operator==(const drinkStack<T>& otherStack) const
{
	if (this == &otherStack)
		return true;
	else
		if (stackTop != otherStack.stackTop)
			return false;
		else
		{
			for (int i = 0; i < stackTop; i++)
			{
				if (list[i] != otherStack.list[i])
					return false;
			}
			return true;
		}

}

template<class T>
void drinkStack<T>::writeToFileCurrentSession( const T* currentDrink)
{
	ofstream outFile;
	outFile.open("currentSession.txt", std::ios_base::app);
	
	if (outFile)
	{
		
		
		outFile << currentDrink->beerTreeObject;
		push(currentDrink);
		

		outFile.close();
	}
	else
	{
		cout << "something went wrong"; // don't like this
	}
}

template<class T>
void drinkStack<T>::writeToFileEndOfSession( const T* currentDrinkList)
{
	ofstream outFile;
	outFile.open("previousSession.txt", std::ios_base::app);

	if (outFile)
	{
			for (int i = stackTop; i < 0; i--)
			{
				outFile << top();
				outFile << '\n';
				pop(); // might cause memory leak...
			}
			
		outFile.close();
	}
	else
	{
		cout << "something went wrong"; // don't like this
	}
}


