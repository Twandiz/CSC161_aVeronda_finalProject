#include "BeerDataBase.h"


BeerDataBase::BeerDataBase()
{
	populateBeerDB();
}

BeerDataBase::~BeerDataBase()
{
	/*for (int i = 0; i < beerDBObj.size(); i++)
	{
		beerDBObj[i];
	}*/
	
}

void BeerDataBase::populateBeerDB()
{

	ifstream inFile;
	inFile.open("drinkDB.txt");
	int count = 0;
	char getDBEntry[100];
	Beer beerInfo;



	if (inFile)
	{
		inFile.ignore(10000, '!');

		while (inFile.good()) // .eof didn't work for some reason, not sure why, 
		{
			for (int i = 0; i < count; i++)
			{
				inFile.ignore(1000, '/n');
			}
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
			//getDBEntry.clear();

			beerDBObjQue.push_back(beerInfo);

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
}

// searches beer DB for string value name, returns beer object, might change to return pointer, 
// lower overhead...
Beer BeerDataBase::searchDB( string& searchItem)
{

	string tempName;
	Beer validation;

	transform(searchItem.begin(), searchItem.end(), searchItem.begin(), ::tolower);


	for (int i = 0; i < beerDBObjQue.size(); i++)
	{
		tempName = beerDBObjQue[i].name;
		transform(tempName.begin(), tempName.end(), tempName.begin(), tolower);

		if ( tempName == searchItem)
		{
			return  beerDBObjQue[i];
		}
	}

	return validation;
}


// print function, could be abstracted, don't like cout outside main, no time
void BeerDataBase::printBeerDB()
{
	int temp = beerDBObjQue.size();
	for (int i = 0; i < beerDBObjQue.size(); i++)
	{
		cout << i << " " << beerDBObjQue[i] << endl;
	}
	
}


// validate return objects
bool BeerDataBase::isValidReturn(Beer& testObj)
{
	for (int i = 0; i < beerDBObjQue.size(); i++)
	{
		if (beerDBObjQue[i] == testObj)
		{
			return  true;
		}
	}

	return false;
}


