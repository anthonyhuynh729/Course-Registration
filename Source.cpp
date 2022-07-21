#include "Header.h"
#include "user.h"
#include "student.h"
#include "instructor.h"
#include "admin.h"

int main() {

	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;
	sql = "PRAGMA journal_mode=WAL;";
	sqlite3_exec(db, sql.c_str(), NULL, 0, NULL);

	user user1("NULL", "NULL", "NULL");
	student student1("NULL", "NULL", "NULL");
	instructor instructor1("NULL", "NULL", "NULL");
	admin admin1("NULL", "NULL", "NULL");


	int userSelection = 0;
	int ID;
	string CRNS;
	string courseName;
	string dept;
	int time;
	string days;
	string semester;
	int year;
	int credits;

	while (1) {
		user1.logIn();
		string fname = user1.checkFirst();
		string lname = user1.checkLast();
		string ID = user1.checkID();

		int userType = ID[0] - '0';

		switch (userType) {
		case 1:
			student1.setAttributes(fname, lname, ID);
			cout << "What would you like to do?" << endl;
			cout << "1. Add a course" << endl;
			cout << "2. Remove a course" << endl;
			cout << "3. Search all courses" << endl;
			cout << "4. Search courses with parameters" << endl;
			cout << "5. Logout" << endl;

			cin >> userSelection;

			switch (userSelection) {
			case 1:
				cout << "Adding a Course:" << endl;
				cout << "Enter the CRNs: ";
				cin.ignore();
				getline(cin, CRNS);

				student1.addCourse(ID, CRNS);
				break;
			case 2:
				cout << "Removing a Course: ";
				cout << "Enter the CRNs: ";
				cin.ignore();
				getline(cin, CRNS);

				student1.removeCourse(ID, CRNS);
				break;
			case 3:
				cout << "Searching All Courses: ";
				student1.searchAllCourses();
				break;
			case 4:
				cout << "Searching courses with parameters";
				student1.searchCourses();
				break;
			case 5:
				student1.logOut();
				break;
			default:
				cout << "Invalid..." << endl;
				cout << "Please Try Again" << endl;
				cout << endl;
				break;
			}
			break;

		case 2:
				instructor1.setAttributes(fname, lname, ID);
				cout << "What would you like to do?" << endl;
				cout << "1. Add a course" << endl;
				cout << "2. Remove a course" << endl;
				cout << "3. Print Course Roster" << endl;
				cout << "4. Search all courses" << endl;
				cout << "5. Search courses with parameters" << endl;
				cout << "6. Logout" << endl;

				cin >> userSelection;

				switch (userSelection) {
				case 1:
					cout << "Adding a Course:" << endl;
					cout << "Enter the CRNs: ";
					cin.ignore();
					getline(cin, CRNS);

					instructor1.addCourse(ID, CRNS);
					break;
				case 2:
					cout << "Removing a Course: ";
					cout << "Enter the CRNs: ";
					cin.ignore();
					getline(cin, CRNS);

					instructor1.removeCourse(ID, CRNS);
					break;
				case 3:
					cout << "Print Course Roster: ";

					instructor1.printSchedule(ID);
					break;
				case 4:
					cout << "Searching All Courses: ";
					instructor1.searchAllCourses();
					break;
				case 5:
					cout << "Searching courses with parameters";
					instructor1.searchCourses();
					break;
				case 6:
					instructor1.logOut();
					break;
				default:
					cout << "Invalid..." << endl;
					cout << "Please Try Again" << endl;
					cout << endl;
					break;
				}
				break;
			case 3:
				admin1.setAttributes(fname, lname, ID);
				cout << "What would you like to do?" << endl;
				cout << "1. Add a course" << endl;
				cout << "2. Remove a course" << endl;
				cout << "3. Search all courses" << endl;
				cout << "4. Search courses with parameters" << endl;
				cout << "5. Logout" << endl;

				cin >> userSelection;

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
					cout << "Removing a Course: ";
					cout << "Enter the CRN: ";
					cin >> ID;
					admin1.removeCourse(ID);
					break;
				case 3:
					cout << "Searching All Courses: ";
					admin1.searchAllCourses();
					break;
				case 4:
					cout << "Searching courses with parameters";
					admin1.searchCourses();
					break;
				case 5:
					admin1.logOut();
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