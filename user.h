#pragma once
#include "Header.h"

class user
{
protected:
	string firstName;
	string lastName;
	string userID;
	string userEmail;

public:
	//Default constructor
	user();

	//Constructor with parameters
	user(string first, string last, string ID);

	// Methods to return the users first name, last name, and user ID
	string checkFirst();
	string checkLast();
	string checkID();

	// Sets the user's attributes to the defined values
	void setAttributes(string fName, string lName, string ID);

	// Method to print out all of the user's information
	void checkAll();

	void searchAllCourses();

	void searchCourses();

	void logIn();
	void logOut();

	~user();
};

