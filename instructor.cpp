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

void instructor::addCourse(string ID, string CRNS) // Adds a course 
{
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;
	string tempCourses ="";

	//Searches for current list of courses
	sql = "Select COURSES From INSTRUCTOR Where ID = " + ID + " ;";
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	auto tempCRNS = sqlite3_column_text(stmt, 0);
	size_t s = sqlite3_column_bytes(stmt, 0);
	tempCourses = (s > 0 ? string((const char*)tempCRNS, s) : "");

	// If the first character is a space, deletes it
	while (CRNS[0] == ' ') {
		CRNS.erase(0, 1);
	}

	// If the final character is a space, deletes it
	if (tempCourses.length() != 0) {
		while (tempCourses[tempCourses.length() - 1] == ' ') {
			tempCourses.erase(tempCourses.length() - 1, 1);
		}
	}

	string CRN = tempCourses + " " + CRNS;

	// If the first character is a space, deletes it
	while (CRN[0] == ' ') {
		CRN.erase(0, 1);
	}

	CRN = CRN + " ";

	// Creates the string and then executes it
	sql = "UPDATE INSTRUCTOR SET COURSES = '" + CRN + "' WHERE ID = " + ID;
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

void instructor::removeCourse(string ID, string CRNS) // Removes a course (Inderdeep)
{
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;
	string tempCourses;
	string CRN = CRNS;
	string tempCRN;

	sql = "SELECT COURSES FROM INSTRUCTOR WHERE ID = " + ID;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	auto first = sqlite3_column_text(stmt, 0);
	size_t s = sqlite3_column_bytes(stmt, 0);
	tempCRN = (s > 0 ? string((const char*)first, s) : "");

	// Checks to see if the CRN exists inside of the current CRNS
	string::size_type i = tempCRN.find(CRN);

	if (i != string::npos) {
		tempCRN.erase(i, CRN.length());
		while (tempCRN[0] == ' ') {
			tempCRN.erase(0, 1);
		}
		sql = "UPDATE INSTRUCTOR SET COURSES = '" + tempCRN + "' WHERE ID = " + ID;
		exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
		// Outputs whether the course was successfully removed
		if (exit != SQLITE_OK) {
			std::cerr << "Error Removing Courses" << endl;
		}
		else
			cout << "Course Removed Successfully" << endl;
	}
	else {
		cout << "CRN was not originally in courses list." << endl;
		cout << "Aborted Action" << endl;
	}



	//Searches for current list of courses
	sql = "SELECT COURSES FROM INSTRUCTOR WHERE ID = " + ID;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	first = sqlite3_column_text(stmt, 0);
	s = sqlite3_column_bytes(stmt, 0);
	tempCRN = (s > 0 ? string((const char*)first, s) : "");

	cout << "Current courses: " << tempCRN << endl;


	sqlite3_close(db);
}

void instructor::printSchedule(string ID) // Prints instructors schedule, currently does nothing
{
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;
	string tempCourses;

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

void instructor::printCourseRoster(string ID) // Prints class list
{
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;
	string tempCourses;

	//Searches for current list of courses
	sql = "Select COURSES From INSTRUCTOR Where ID = " + ID + " ;";
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	auto tempCRNS = sqlite3_column_text(stmt, 0);
	size_t s = sqlite3_column_bytes(stmt, 0);
	tempCourses = (s > 0 ? string((const char*)tempCRNS, s) : "");

	cout << "Current courses: " << tempCourses << endl;

	string space_delimiter = " ";
	vector<string> course{};

	size_t pos = 0;
	while ((pos = tempCourses.find(space_delimiter)) != string::npos) {
		course.push_back(tempCourses.substr(0, pos));
		tempCourses.erase(0, pos + space_delimiter.length());
	}
	
	// Goes through every course the instructor teaches
	// Prints first and last name of students that are also in that course
	for (const auto& str : course) {
		sql = "SELECT TITLE FROM COURSES WHERE CRN = " + str;
		//cout << sql << endl;
		exit = sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);
		cout << "Students: " << endl;
		sql = "SELECT NAME, SURNAME FROM STUDENT WHERE COURSES LIKE '%" + str + "%'";
		//cout << sql << endl;
		exit = sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);
	}


	sqlite3_close(db);
}
