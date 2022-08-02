#include "user.h"


user::user() // Default constructor
{
	firstName = "John";
	lastName = "Smith";
	userID = "W00123456";
}


user::user(string first, string last, string ID) // Constructor with user defined attributes. Adds W00 to ID
{
	firstName = first;
	lastName = last;
	userID = ID;
}

user::~user() // Default destructor
{

}

string user::checkFirst() // Returns users first name
{
	return firstName;
}

string user::checkLast()  // Returns users last name
{
	return lastName;
}

string user::checkID()  // Returns users ID
{
	return userID;
}


void user::setAttributes(string fName, string lName, string ID) {
	firstName = fName;
	lastName = lName;
	userID = ID;
}

void user::checkAll() // Prints out user's attributes
{
	cout << "First Name: " << firstName << endl;
	cout << "Last Name: " << lastName << endl;
	cout << "User ID: " << userID << endl;
}

void user::searchAllCourses() // Prints out all courses available (Inderdeep)
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;

	sql = "Select * From Courses";
	exit = sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);

	sqlite3_close(db);
}


void user::searchCourses() // Prompts user for which parameters they would like to search for (Inderdeep)
{
	// Opens users databse
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql = "Select * From Courses Where";
	int exit;
	char* messageError;

	int paramChoice = 0;
	string CRN;
	//char title[256];
	string title;
	string dept;
	string time;
	//char days[256];
	string days;
	string semester;
	string year;
	string credits;

	cout << "Course Parameters include: CRN, Title, Department, Time, Day, Semester, Year, Credits" << endl;
	// Runs a loop until user chooses to search
	while (paramChoice != 9) {
		cout << "Which Parameter woud you like to define?" << endl;
		cout << "(Note: Selecting a parameter more than once will invalidate the search)" << endl;
		cout << "1. CRN" << endl;
		cout << "2. Title" << endl;
		cout << "3. Department" << endl;
		cout << "4. Time (24 hour)" << endl;
		cout << "5. Day (M T W R F)" << endl;
		cout << "6. Semester" << endl;
		cout << "7. Year" << endl;
		cout << "8. Credits" << endl;
		cout << "9. Search for Courses" << endl;
		cin >> paramChoice;
		
		// Prompts user for a parameter depending on which one they want to search for
		switch (paramChoice) {
		case 1:
			cout << "Enter the CRN: ";
			cin >> CRN;
			sql = sql + " CRN = " + CRN + " and";
			cout << endl;
			break;
		case 2:
			cout << "Enter the Title: ";
			cin.ignore();
			//std::cin.getline(title, 20);
			getline(cin, title);

			sql = sql + " TITLE = '" + title + "' and";
			cout << endl;
			break;
		case 3:
			cout << "Enter the Department Name: ";
			cin >> dept;
			sql = sql + " DEPARTMENT = '" + dept + "' and";
			cout << endl;
			break;
		case 4:
			cout << "Enter the Time(Ex: 1800): ";
			cin >> time;
			sql = sql + " TIME = '" + time + "' and";
			cout << endl;
			break;
		case 5:
			cout << "Enter the Days(Ex: M W R): ";
			cin.ignore();
			//std::cin.getline(days, 20);
			getline(cin, days);
			sql = sql + " DAY = '" + days + "' and";
			//cout << days;
			cout << endl;
			break;
		case 6:
			cout << "Enter the Semester(Ex: Spring): ";
			cin >> semester;
			sql = sql + " SEMESTER = '" + semester + "' and";
			cout << endl;
			break;
		case 7:
			cout << "Enter the Year(Ex: 2023): ";
			cin >> year;
			sql = sql + " YEAR = " + year + " and";
			cout << endl;
			break;
		case 8:
			cout << "Enter the Credits(Ex: 4): ";
			cin >> credits;
			sql = sql + " CREDITS = " + credits + " and";
			cout << endl;
			break;
		case 9:
			cout << "Searching..." << endl;
			cout << endl;
			break;
		default:
			cout << "Invalid..." << endl;
			cout << "Please Try Again" << endl;
			cout << endl;
			break;
			
		}
	}

	//cout << sql << endl;
	sql.erase(sql.end() - 4, sql.end()); // Removes any extra "and" at the end
	sql = sql + ";";
	//cout << sql << endl;

	exit = sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);

	sqlite3_close(db);
}

void user::logIn() { // Asks user for ID and Email and checks if they match (Inderdeep)
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;

	string tempID;
	string tempEmail;
	int userType;
	cout << "Welcome to Course Manager 3000" << endl;

	
	while (1) {
		cout << "Please enter your User ID (Ex: 12345)" << endl;
		cin >> userID;

		cout << "Please enter your email (Ex: lastF)" << endl;
		cin >> userEmail;

		userType = userID[0] - '0';

		// Depending on user type, searches corresponding table
		switch (userType) {
		case 1:
			sql = "Select EMAIL from Student Where ID = " + userID;
			break;
		case 2:
			sql = "Select EMAIL from INSTRUCTOR Where ID = " + userID;
			break;
		case 3:
			sql = "Select EMAIL from ADMIN Where ID = " + userID;
			break;
		}

		sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
		sqlite3_step(stmt);
		auto first = sqlite3_column_text(stmt, 0);
		size_t s = sqlite3_column_bytes(stmt, 0);
		tempEmail = (s > 0 ? string((const char*)first, s) : "");

		// If the user types the correct email, then proceeds to the rest of login
		if (tempEmail == userEmail) {
			cout << "Login Successful" << endl;

			switch (userType) {
			case 1:
				sql = "Select NAME from Student Where ID = " + userID;
				break;
			case 2:
				sql = "Select NAME from INSTRUCTOR Where ID = " + userID;
				break;
			case 3:
				sql = "Select NAME from ADMIN Where ID = " + userID;
				break;
			}

			sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
			sqlite3_step(stmt);
			first = sqlite3_column_text(stmt, 0);
			s = sqlite3_column_bytes(stmt, 0);
			this->firstName = (s > 0 ? string((const char*)first, s) : "");

			switch (userType) {
			case 1:
				sql = "Select SURNAME from Student Where ID = " + userID;
				break;
			case 2:
				sql = "Select SURNAME from INSTRUCTOR Where ID = " + userID;
				break;
			case 3:
				sql = "Select SURNAME from ADMIN Where ID = " + userID;
				break;
			}

			sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
			sqlite3_step(stmt);
			first = sqlite3_column_text(stmt, 0);
			s = sqlite3_column_bytes(stmt, 0);
			this->lastName = (s > 0 ? string((const char*)first, s) : "");

			cout << "Welcome " << this->firstName << " " << this->lastName << endl;
			break;
		}
		else {
			cout << "Login Failed" << endl;
			cout << "ID or Email is incorrect..." << endl;
			cout << "Please try again" << endl;
		}
	}
	sqlite3_close(db);
}

void user::logOut() {
	// If logout is called the resets all the user attributes
	cout << "You have been logged out." << endl;

	userID = "000000";
	firstName = "NULL";
	lastName = "NULL";

}