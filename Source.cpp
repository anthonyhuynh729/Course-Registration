#include "Header.h"
#include "user.h"
#include "student.h"
#include "instructor.h"
#include "admin.h"

int main(int argc, char* argv[]) {

	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;
	sql = "PRAGMA journal_mode=WAL;";
	sqlite3_exec(db, sql.c_str(), NULL, 0, NULL);

	// Creates objects for base user and each user class
	// Objects need to be created at the beginning due to C++ compilation
	user user1("NULL", "NULL", "NULL");
	student student1("NULL", "NULL", "NULL");
	instructor instructor1("NULL", "NULL", "NULL");
	admin admin1("NULL", "NULL", "NULL");

	// Variables that control the log in loop
	int loopTrue = 1;
	int loggedIn = 0;

	// Variables that will be used later on
	int userSelection = 0;
	string ID;
	string CRNS;
	string courseName;
	string dept;
	int time;
	string days;
	string semester;
	int year;
	int credits;

	// Prompts user to log in and sets loggedIn to 1
	user1.logIn();
	loggedIn = 1;
	
	// This loops until user logs out
	while (loggedIn) {
		// Checks the user's first name, last name, and ID
		string fname = user1.checkFirst();
		string lname = user1.checkLast();
		ID = user1.checkID();

		// Calculates what type of the user is
		// Admin IDs start with 3, Instructor IDs start with 2, Student IDs start with 1
		int userType = ID[0] - '0';

		// Depending on what type of user they are, different options are shown
		switch (userType) {
		case 1:
			// Sets the student's attributes
			student1.setAttributes(fname, lname, ID);
			cout << "What would you like to do?" << endl;
			cout << "1. Add a course" << endl;
			cout << "2. Remove a course" << endl;
			cout << "3. Print Course Schedule" << endl;
			cout << "4. Check for Schedule Conflicts" << endl;
			cout << "5. Search all courses" << endl;
			cout << "6. Search courses with parameters" << endl;
			cout << "7. Logout" << endl;

			cin >> userSelection;
			// Depending on the user's attributes, executes different student methods
			switch (userSelection) {
			case 1:
				cout << "Adding a Course:" << endl;
				cout << "Enter the CRNs: ";
				cin.ignore();
				getline(cin, CRNS);

				student1.addCourse(ID, CRNS);
				break;
			case 2:
				cout << "Removing a Course: " << endl;
				cout << "Enter the CRNs: ";
				cin.ignore();
				getline(cin, CRNS);

				student1.removeCourse(ID, CRNS);
				break;
			case 3:
				cout << "Printing Schedule: " << endl;
				student1.printSchedule(ID);
				break;
			case 4:
				cout << "Checking for Conflicts..." << endl;
				student1.checkConflicts(ID);
				break;
			case 5:
				cout << "Searching All Courses: " << endl;
				student1.searchAllCourses();
				break;
			case 6:
				cout << "Searching courses with parameters" << endl;
				student1.searchCourses();

				break;
			case 7:
				student1.logOut();
				loggedIn = 0;
				break;
			default:
				cout << "Invalid..." << endl;
				cout << "Please Try Again" << endl;
				cout << endl;
				break;
			}
			break;

		case 2:
			// Sets the instructors's attributes
			instructor1.setAttributes(fname, lname, ID);
			cout << "What would you like to do?" << endl;
			cout << "1. Add a course" << endl;
			cout << "2. Remove a course" << endl;
			cout << "3. Print Teaching Schedule" << endl;
			cout << "4. Print Course Roster" << endl;
			cout << "5. Search all courses" << endl;
			cout << "6. Search courses with parameters" << endl;
			cout << "7. Logout" << endl;

			cin >> userSelection;
			// Depending on the user's attributes, executes different instructor methods
			switch (userSelection) {
			case 1:
				cout << "Adding a Course:" << endl;
				cout << "Enter the CRNs: ";
				cin.ignore();
				getline(cin, CRNS);
				cout << endl;
				instructor1.addCourse(ID, CRNS);
				break;
			case 2:
				cout << "Removing a Course: ";
				cout << "Enter the CRNs: ";
				cin.ignore();
				getline(cin, CRNS);
				cout << endl;
				instructor1.removeCourse(ID, CRNS);
				break;
			case 3:
				cout << "Printing Teaching Schedule: " << endl;
				instructor1.printSchedule(ID);
				break;
			case 4:
				cout << "Printing Course Roster: " << endl;
				instructor1.printCourseRoster(ID);
				break;
			case 5:
				cout << "Searching All Courses: " << endl;
				instructor1.searchAllCourses();
				break;
			case 6:
				cout << "Searching courses with parameters" << endl;
				instructor1.searchCourses();
				break;
			case 7:
				instructor1.logOut();
				loggedIn = 0;
				break;
			default:
				cout << "Invalid..." << endl;
				cout << "Please Try Again" << endl;
				cout << endl;
				break;
			}
			break;
		case 3:
			// Sets the instructors's attributes
			admin1.setAttributes(fname, lname, ID);
			cout << "What would you like to do?" << endl;
			cout << "1. Add a course" << endl;
			cout << "2. Remove a course" << endl;
			cout << "3. Add a user" << endl;
			cout << "4. Remove a user" << endl;
			cout << "5. Search all courses" << endl;
			cout << "6. Search courses with parameters" << endl;
			cout << "7. Link a course with a user" << endl;
			cout << "8. Unlink a course with a user" << endl;
			cout << "9. Logout" << endl;

			cin >> userSelection;

			// Depending on the user's attributes, executes different admin methods
			switch (userSelection) {
			case 1:
				cout << "Adding a Course:" << endl;

				cout << "Enter the CRN: ";
				cin >> ID;
				cout << "Enter the Title: ";
				cin.ignore();
				getline(cin, courseName);
				cout << "Enter the Department Name: ";
				cin >> dept;
				cout << "Enter the Time(Ex: 1800): ";
				cin >> time;
				cout << "Enter the Days(Ex: M W R): ";
				cin.ignore();
				getline(cin, days);
				cout << "Enter the Semester(Ex: Spring): ";
				cin >> semester;
				cout << "Enter the Year(Ex: 2023): ";
				cin >> year;
				cout << "Enter the Credits(Ex: 4): ";
				cin >> credits;

				admin1.addCourse(ID, courseName, dept, time, days, semester, year, credits);
				break;
			case 2:
				cout << "Removing a Course: " << endl;
				cout << "Enter the CRN: ";
				cin >> ID;
				admin1.removeCourse(ID);
				break;
			case 3:
				cout << "Adding a User:" << endl;
				admin1.addUser();
				break;
			case 4:
				cout << "Removing a User:" << endl;
				admin1.removeUser();
				break;
			case 5:
				cout << "Searching All Courses: " << endl;
				admin1.searchAllCourses();
				break;
			case 6:
				cout << "Searching courses with parameters" << endl;
				admin1.searchCourses();
				break;
			case 7:
				cout << "Linking Course: " << endl;
				admin1.linkUserCourse();
				break;
			case 8:
				cout << "Unlinking Course: " << endl;
				admin1.unlinkUserCourse();
				break;
			case 9:
				admin1.logOut();
				loggedIn = 0;
				break;
			default:
				cout << "Invalid..." << endl;
				cout << "Please Try Again" << endl;
				cout << endl;
				break;

			}
			break;
		}



	}
	
	sqlite3_close(db);
	return 0;
}