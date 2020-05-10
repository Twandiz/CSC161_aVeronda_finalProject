#include "user.h"

user::user()
{
	name = "Something went wrong";
	age = 21;
	sex = 'u';
	weight = 150;
	newUser = true;
	justCreated = true;
}

user::user(std::string newName, int newAge, char newSex, int newWeight)
{
	name = newName;
	age = newAge;
	sex = newSex;
	weight = newWeight;
	newUser = true;
	justCreated = true; // dowhile loop of read in and check in main()
}

user::~user()
{
}

bool user::isNewUser()
{
	return this->newUser;
}


// needs user name check to be moved to main::userLoginMain()
user user::userLogin( std::string& userName)
{
	std::ifstream inFile;
	//std::ofstream outfile;
	user tempUser;

	std::string userNameFromFile;
	std::string temp;
	//int tempInt;

	inFile.open("userDB.txt");

	if (inFile)
	{
		inFile.ignore(10000, '$');
		std::getline(inFile, userNameFromFile, '_');

		temp = userNameFromFile;
		std::for_each(temp.begin(), temp.end(), [](char& c) 
		{
			c = ::tolower(c);
		});
	}

	std::for_each(userName.begin(), userName.end(), [](char& c)
		{
			c = ::tolower(c);
		});

	if (temp == userName)
	{
		tempUser.name = userNameFromFile;
		//inFile.ignore(1000, '_');

		std::getline(inFile, userNameFromFile, '_');
		tempUser.age = std::stoi(userNameFromFile);

		std::getline(inFile, userNameFromFile, '_');
		tempUser.sex = userNameFromFile[0];

		std::getline(inFile, userNameFromFile, '_');
		tempUser.weight = std::stoi(userNameFromFile);

		std::getline(inFile, userNameFromFile, '_');
		tempUser.newUser = std::stoi(userNameFromFile);

		std::getline(inFile, userNameFromFile, '_');
		tempUser.justCreated = std::stoi(userNameFromFile);
	}

	inFile.close();

	return tempUser;
}

std::string user::displayUserName(user& userObj)
{
	return userObj.name;
}

//void user::currentABV(drink)
//{
//
//}
