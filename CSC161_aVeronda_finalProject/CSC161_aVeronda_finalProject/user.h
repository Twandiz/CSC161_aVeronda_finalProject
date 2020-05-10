#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>

//using namespace std;

// User class to add extra functionallity, reads from userDB.txt

class user 
{
private:
	std::string name;
	int age;
	char sex;
	int weight;
	bool newUser;
	bool justCreated;

public:
	
	user();
	user(std::string, int, char, int );

	~user();

	bool isNewUser();
	user userLogin( std::string& );
	std::string displayUserName(user&);
	//void currentABV( drink ); // main calculation for abv, constantly polling

};

