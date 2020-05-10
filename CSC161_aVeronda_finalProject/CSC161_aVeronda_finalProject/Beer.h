#pragma once
#include <string>
#include <iostream>
#include <deque>
#include "drinkStack.h"


using namespace std;

// works with graph to offer sugestions for next drink
// TODO: operator overrides for comparison user in graph implementation
//		change hoppiness into IBU conversion
// main class, should have been virtual to show off polymorphism, 
// creates beer object
class Beer 
{
public:	

	double abv;				// alchohol by volume
	string name;			// name of beer
	string type;			// type of beer
	int hoppiness;			// 0-10 for scale of hopiness
	int darkness;			// 0-10 for darknes of beer
	string producer;		// name of brewery
	bool microBrew;			// microbrew or not
	bool drankPreviously;	// whether user has consumed or not
	bool likedDrink;		// whether user has liked drink
	


	Beer();
	~Beer();

	

	


	bool operator==(const  Beer& other) const
	{
		if (name == other.name)
		{
			return true;
		}
		if (abv == other.abv && name == other.name && producer == other.producer)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator<(const Beer& other)
	{
		if (abv < other.abv && name < other.name && producer < other.producer)
		{
			return true;
		}
		else if (abv == other.abv && name < other.name && producer < other.producer)
		{
			return true;
		}
		else if (abv == other.abv && name < other.name && producer == other.producer)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator>(const Beer& other)
	{
		if (abv > other.abv && name > other.name && producer > other.producer)
		{
			return true;
		}
		else if (abv == other.abv && name > other.name && producer > other.producer)
		{
			return true;
		}
		else if (abv == other.abv && name > other.name && producer == other.producer)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void operator=(const Beer& other) 
	{
		abv = other.abv;
		name = other.name;
		type = other.type;
		hoppiness = other.hoppiness;
		darkness = other.darkness;
		producer = other.producer;
		microBrew = other.microBrew;
		drankPreviously = other.drankPreviously;
		likedDrink = other.likedDrink;
	}

	friend ostream& operator<<(ostream& output, const Beer& other) 
	{
		output << other.name << '\n'
			<< "ABV: " << other.abv << '\n'
			<< "Hoppiness: " << other.hoppiness << '\n'
			<< "Dark Rating: " << other.darkness << '\n'
			<< "Producer: " << other.producer << '\n';
			
		return output;
	}

	friend ofstream& operator<<(ofstream& output, const Beer* other)
	{
		output << other->abv << '_'
			<< other->name << '_'
			<< other->type << '_'
			<< other->hoppiness << '_'
			<< other->darkness << '_'
			<< other->producer << '_'
			<< other->microBrew << '_'
			<< other->drankPreviously << '_'
			<< other->likedDrink << '_';

		return output;
	}
	/*friend istream& operator>>(istream& input, Beer& D)
	{
		input >> D.feet >> D.inches;
		return input;
	}*/


};

inline Beer::Beer()
{
	abv = 0.0;
	name = " ";
	type = " ";
	hoppiness = 0;
	darkness = 0;
	producer = " ";
	microBrew = false;
	drankPreviously = false;
	likedDrink = false;
}

inline Beer::~Beer()
{
	//delete this;
}

