
#pragma

#include <iostream>
#include <string>
#include <deque>
#include "Beer.h"
#include "BeerDataBase.h"
#include "binaryTreeDrinks.h"
#include "user.h"
#include "DrinkGraph.h"
#include "drink.h"
#include "drinkStack.h"


using namespace std;


user userLoginMain( );
void mainMenu( user& );
void addDrinkMain(BeerDataBase&, drink<Beer>&);
void viewCurrentSessionMain(drink<Beer>&);
void viewDrinkRecomendations(DrinkGraph&);


int main() 
{
	
	cout << "Welcome to the Beer Companion App\n\n";
	user realUser = userLoginMain(  );

	system("CLS");

	mainMenu( realUser );


	

	



	system("pause");
	return 0;
}



// user login function, checks to see if returning user
user userLoginMain()
{
	char singleDigitAnswer;
	string answer;
	int age, weight;
	char sex;
	user newUserObj;

	do
	{
		cout <<"Are you a returning user(y/n): ";
		cin >> singleDigitAnswer;
		singleDigitAnswer = tolower(singleDigitAnswer);

	} while (singleDigitAnswer != 'y' && singleDigitAnswer != 'n');

	if (singleDigitAnswer == 'n')
	{
		cout << "Let's create a profile..."
			"\nPlease enter your desired user name: ";
		cin.ignore(10000, '\n');
		getline(cin, answer);
		cout << "\nPlease enter your desired user age: ";
		cin >> age;
		if (age < 21)
		{
			cout << "YOU ARE NOT AUTHORIZED!";
			exit(-1);
		}
		do
		{
			cout << "\nPlease enter your gender (M/F): ";
			cin >> sex;
			sex = toupper(sex);
		} while (sex != 'M' && sex != 'F');
		cout << "\nPlease enter your weight: ";
		cin >> weight;

		newUserObj = user(answer, age, sex, weight);
	}
	else
	{
		cout << "\nPlease enter your user name:	";
		cin.ignore(10000, '\n');
		getline(cin,answer);

		newUserObj = newUserObj.userLogin(answer);
	}

	return newUserObj;
}

// switch statement run in main to out put menu
void mainMenu(user& userObj)
{

	int choice = 0;
	BinaryTreeDrinks<Beer> beerList;
	DrinkGraph graphBeer;
	BeerDataBase beerQue;
	drink<Beer> drinkBeerObject;
	

	do
	{

	cout << "Welcome to the Beer Companion App\n";
	cout << userObj.displayUserName(userObj) << endl;
	cout << "\nPlease make a Selection from the following menu:"
		<< "\n1: View drinks in database."
		<< "\n2: Add a drink to your current session."
		<< "\n3: View your current session."
		<< "\n4: View your drink recomendations."
		<< "\n5: Quit\n";
	cin >> choice;

		switch (choice)
		{
		case 1:

			beerList.displayInOrder();
			system("pause");
			choice = 0;
			break;

		case 2:
			
			addDrinkMain(beerQue, drinkBeerObject);

			choice = 0;
			break;
		case 3:

			viewCurrentSessionMain(drinkBeerObject);

			choice = 0;
			break;
		case 4:
			
			viewDrinkRecomendations(graphBeer);
			choice = 0;
			break;
		case 5:

			choice = 1;
			break;
		default:

			cout << "\nPlease make an appropriate selection...\n";
			choice = 0;
			break;
		}


		system("CLS");
	} while (choice == 0);

}

// adds drink from list to current session que
void addDrinkMain(BeerDataBase& beerBDO, drink<Beer>& beerList )
{
	system("CLS");
	beerBDO.printBeerDB();

	int count = 0;
	Beer tempBeer;
	string searchFor;
	bool testReturn = false;

	do {

		if (count > 0)
		{
			cout << "Please make an appropriate selection from the list above...\n";
		}
		cout << "Please enter the name of the beer you drank: \n";
		if (count == 0)
		{
			cin.ignore(10000, '\n');
		}
		getline(cin, searchFor);

		tempBeer = beerBDO.searchDB(searchFor);
		count++;
	} while (beerBDO.isValidReturn(tempBeer) == false);
	//cout << "found it";
	
	beerList.addDrink(tempBeer);

	system("CLS");

	cout << "Drink Added!\n\n";
}


// just can't get it to work the way I want, coped out
// function to read out current session, currently reads from current session file
void viewCurrentSessionMain( drink<Beer> &currentSessionQue )
{
	//drink<Beer> temp;
	//cout << currentSessionQue.getFront();
	//for (int i = 0; i < currentSessionQue.size(); i++)
	//{
	//	currentSessionQue.printQue(currentSessionQue);
	//	//temp = currentSessionQue.getNext(currentSessionQue.getFront());
	//}

	ifstream inFile;
	inFile.open("currentSession.txt");
	int count = 0;
	char getDBEntry[100];
	Beer beerInfo;
	deque<Beer> copOutQue;



	if (inFile)
	{
		inFile.ignore(10000, '%');

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

			copOutQue.push_back(beerInfo);

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

	system("CLS");
	cout << "Your Current Session: \n\n";

	for (int i = 0; i < copOutQue.size(); i++)
	{
		cout << copOutQue[i];
	}
	system("pause");
}


// Unable to configure graph in time, requires better setWeight algorithm to produce better weights, for now just prints 
// (source, destination, weight)
// program to output graph based recomendations, incomplete
void viewDrinkRecomendations( DrinkGraph& currentGraph)
{

	
	currentGraph.printGraph(currentGraph);
	system("pause");
}

