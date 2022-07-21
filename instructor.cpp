#include "instructor.h"

instructor::instructor(string first, string last, string ID) // Constructor with user defined attributes. Adds W00 to ID
{
	firstName = first;
	lastName = last;
	userID = ID;
}

void instructor::setAttributes(string first, string last, string ID) // Constructor with user defined attributes. Adds W00 to ID
{
	firstName = first;
	lastName = last;
	userID = ID;
}

void instructor::addCourse(string ID, string CRNS) // Adds a course (Anthony)
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
	sql = "Select COURSES From INSTRUCTOR Where ID = " + ID + " ;";
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	auto tempCRNS = sqlite3_column_text(stmt, 0);
	size_t s = sqlite3_column_bytes(stmt, 0);
	tempCourses = (s > 0 ? string((const char*)tempCRNS, s) : "");

	// Creates the string and then executes it
	sql = "Update INSTRUCTOR Set COURSES = COURSES || " + CRNS + " || ' ' Where ID = " + ID + "; ";
	cout << sql;

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

void instructor::removeCourse(string ID, string CRNS) // Removes a course (Anthony)
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
	sql = "Update INSTRUCTOR Set COURSES = REPLACE(COURSES," + CRNS + " || ' ','') Where ID = " + ID + "; ";
	exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

	// Outputs whether the course was successfully added
	if (exit != SQLITE_OK) {
		std::cerr << "Error Adding Courses" << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Course Removed Successfully" << endl;

	//Searches for current list of courses
	sql = "Select COURSES From INSTRUCTOR Where ID = " + ID + " ;";
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	auto tempCRNS = sqlite3_column_text(stmt, 0);
	size_t s = sqlite3_column_bytes(stmt, 0);
	tempCourses = (s > 0 ? string((const char*)tempCRNS, s) : "");

	cout << "Current courses: " << tempCourses << endl;

	sqlite3_close(db);
}

void instructor::printSchedule(string ID) // Prints instructors schedule (Anthony)
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
	sql = "Select COURSES From INSTRUCTOR Where ID = " + ID + " ;";
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	auto tempCRNS = sqlite3_column_text(stmt, 0);
	size_t s = sqlite3_column_bytes(stmt, 0);
	tempCourses = (s > 0 ? string((const char*)tempCRNS, s) : "");

	//cout << "Current courses: " << tempCourses << endl;

	sqlite3_close(db);

	string space_delimiter = " ";
	vector<string> course{};

	size_t pos = 0;
	while ((pos = tempCourses.find(space_delimiter)) != string::npos) {
		course.push_back(tempCourses.substr(0, pos));
		tempCourses.erase(0, pos + space_delimiter.length());
	}

	for (const auto& str : course) {
		//cout << str << endl;
		sql = "Select * From Courses Where CRN = "+ str;
		exit = sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);
	}
}

void instructor::printClassList() // Prints class list, currently does nothing
{

}

void instructor::courseSearch() // Searches for courses, currently does nothing
{

}