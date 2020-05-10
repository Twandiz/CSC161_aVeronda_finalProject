#pragma once

#include "Beer.h"
#include <deque>
#include <algorithm>

// Class to lhandle operations on Beer objects
class BeerDataBase :
	public Beer
{
public:

	deque<Beer> beerDBObjQue;		// deque of beers
	deque<Beer>::iterator beerDBit = beerDBObjQue.begin();

	BeerDataBase();
	~BeerDataBase();

	void populateBeerDB();		// used to populate manipulateable queue
	Beer searchDB( string& );	// used to add to drink list
	void printBeerDB();			// prints out DB
	bool isValidReturn(Beer&);	// checks to see if valid beer object returned
};

