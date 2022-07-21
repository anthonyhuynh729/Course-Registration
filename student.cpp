#include "student.h"

student::student(string first, string last, string ID) // Constructor with user defined attributes. Adds W00 to ID
{
	firstName = first;
	lastName = last;
	userID = ID;
}

void student::setAttributes(string first, string last, string ID) // Constructor with user defined attributes. Adds W00 to ID
{
	firstName = first;
	lastName = last;
	userID = ID;
}

void student::courseSearch() // Searches for courses, currently does nothing
{
	
}

void student::addCourse(string ID, string CRNS) // Adds a course (Anthony)
{
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;
	string tempCourses = " ";

	//Searches for current list of courses
	sql = "Select COURSES From STUDENT Where ID = " + ID + " ;";
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	auto tempCRNS = sqlite3_column_text(stmt, 0);
	size_t s = sqlite3_column_bytes(stmt, 0);
	tempCourses = (s > 0 ? string((const char*)tempCRNS, s) : "");
	cout << tempCourses << endl;

	// Creates the string and then executes it
	sql = "Update STUDENT Set COURSES = COURSES || " + CRNS + " || ' ' Where ID = " + ID + "; ";
	exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

	// Outputs whether the course was successfully added
	if (exit != SQLITE_OK) {
		std::cerr << "Error Adding Courses" << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Course Added Successfully" << endl;

	cout << "Current courses: " << tempCourses + " " + CRNS << endl;


	sqlite3_close(db);
}

void student::removeCourse(string ID, string CRNS) // Removes a course (Anthony)
{
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;
	string tempCourses = " ";

	// Creates the string and then executes it
	sql = "Update STUDENT Set COURSES = REPLACE(COURSES," + CRNS + " || ' ','') Where ID = " + ID + "; ";
	exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

	// Outputs whether the course was successfully added
	if (exit != SQLITE_OK) {
		std::cerr << "Error Adding Courses" << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Course Removed Successfully" << endl;

	//Searches for current list of courses
	sql = "Select COURSES From STUDENT Where ID = " + ID + " ;";
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	auto tempCRNS = sqlite3_column_text(stmt, 0);
	size_t s = sqlite3_column_bytes(stmt, 0);
	tempCourses = (s > 0 ? string((const char*)tempCRNS, s) : "");

	cout << "Current courses: " << tempCourses << endl;


	sqlite3_close(db);
}

void student::printSchedule() //Prints students schedule
{

}