#include "admin.h"

admin::admin(string first, string last, string ID) // Constructor with user defined attributes. Adds W00 to ID
{
	firstName = first;
	lastName = last;
	userID = ID;
}

void admin::setAttributes(string fName, string lName, string ID) {
	firstName = fName;
	lastName = lName;
	userID = ID;
}

void admin::addCourse(string ID, string courseName, string dept, int time, string days, string semester, int year, int credits) // Adds a course (Inderdeep)
{
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;

	// Creates the string and then executes it
    sql = "INSERT INTO COURSES VALUES(" + ID + ", '" + courseName + "', '" + dept + "', " + to_string(time) + ", '" + days + "', '" + semester + "', " + to_string(year) + "," + to_string(credits) + ");";
    exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

	// Outputs whether the course was successfully added
    if (exit != SQLITE_OK) {
        std::cerr << "Error Adding Courses" << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Courses Added Successfully" << endl;



	sqlite3_close(db);
}

void admin::removeCourse(string ID) // Removes a course (Inderdeep)
{
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;

	// Creates the string and then executes it
	sql = "Delete From Courses Where CRN = " + ID;
	exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

	// Outputs whether the course was sucessfully deleted
	if (exit != SQLITE_OK) {
		std::cerr << "Error Deleting Course" << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Course Deleted Successfully" << endl;

	sqlite3_close(db);

}

void admin::addUser(string firstName, string lastName, string userID) // Adds a user with first name, last name, and ID
{
	
}

void admin::removeUser(string firstName, string lastName, string userID) // Removes a user, requires first name, last name, and ID
{
	
}

void admin::addStudent(string firstName, string lastName, string userID, string courseName) // Adds a student to a course. Requires first, last, ID, and Course Name
{

}

void admin::removeStudent(string firstName, string lastName, string userID, string courseName) // Removes a student from a course. Requires first, last, ID, and Course Name
{

}

void admin::searchRosters() // Searches for rosters
{

}