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

void student::addCourse(string ID, string CRNS) // Adds a course 
{
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;
	string tempCourses = "";

	//Searches for current list of courses
	sql = "Select COURSES From STUDENT Where ID = " + ID + " ;";
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
	sql = "UPDATE STUDENT SET COURSES = '" + CRN + "' WHERE ID = " + ID;
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

void student::removeCourse(string ID, string CRNS) // Removes a course (Inderdeep)
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

	// Gets current course list from the student
	sql = "SELECT COURSES FROM STUDENT WHERE ID = " + ID;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	auto first = sqlite3_column_text(stmt, 0);
	size_t s = sqlite3_column_bytes(stmt, 0);
	tempCRN = (s > 0 ? string((const char*)first, s) : "");

	// Checks to see if the CRN exists inside of the current CRNS
	string::size_type i = tempCRN.find(CRN);

	// If the crn to remove does exist, executes following code
	if (i != string::npos) {
		tempCRN.erase(i, CRN.length());

		// Erases any leading spaces
		while (tempCRN[0] == ' ') {
			tempCRN.erase(0, 1);
		}

		// Sets student courses to new value
		sql = "UPDATE STUDENT SET COURSES = '" + tempCRN + "' WHERE ID = " + ID;
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
	// Prints current class list 
	sql = "SELECT COURSES FROM STUDENT WHERE ID = " + ID;
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	first = sqlite3_column_text(stmt, 0);
	s = sqlite3_column_bytes(stmt, 0);
	tempCRN = (s > 0 ? string((const char*)first, s) : "");

	cout << "Current courses: " << tempCRN << endl;


	sqlite3_close(db);
}

void student::printSchedule(string ID) //Prints students schedule
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
	sql = "Select COURSES From STUDENT Where ID = " + ID + " ;";
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	auto tempCRNS = sqlite3_column_text(stmt, 0);
	size_t s = sqlite3_column_bytes(stmt, 0);
	tempCourses = (s > 0 ? string((const char*)tempCRNS, s) : "");

	//cout << "Current courses: " << tempCourses << endl;

	
	// Creates a vector called course
	// Treats a space as a delimiter
	string space_delimiter = " ";
	vector<string> course{};

	size_t pos = 0;
	// Iterates through tempCourses and adds it to the course vector
	while ((pos = tempCourses.find(space_delimiter)) != string::npos) {
		course.push_back(tempCourses.substr(0, pos));
		tempCourses.erase(0, pos + space_delimiter.length());
	}

	// Goes through the course vector and prints all classes
	for (const auto& str : course) {
		//cout << str << endl;
		sql = "Select * From Courses Where CRN = " + str;
		exit = sqlite3_exec(db, sql.c_str(), callback, NULL, NULL);
	}

	sqlite3_close(db);
}

void student::checkConflicts(string ID) {
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;
	string tempCourses;
	string tempCourses2;

	int crn1;
	string days1;
	int time1start;
	int time1end;

	int crn2;
	string days2;
	int time2start;
	int mTime;
	int tTime;
	int wTime;
	int rTime;
	int fTime;

	//Searches for current list of courses
	sql = "Select COURSES From STUDENT Where ID = " + ID + " ;";
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	auto tempCRNS = sqlite3_column_text(stmt, 0);
	size_t s = sqlite3_column_bytes(stmt, 0);
	tempCourses = (s > 0 ? string((const char*)tempCRNS, s) : "");
	tempCourses2 = tempCourses;

	//cout << "Current courses: " << tempCourses << endl;

	// Goes through the list of CRNs the student has
	// Iterates through them to add them to a vector
	string space_delimiter = " ";
	vector<string> course{};

	size_t pos = 0;
	while ((pos = tempCourses.find(space_delimiter)) != string::npos) {
		course.push_back(tempCourses.substr(0, pos));
		tempCourses.erase(0, pos + space_delimiter.length());
	}

	// Runs a for loop for each CRN in the vector
	for (const auto& course1check : course) {
		// Gets the days that 'class 1' is taught
		sql = "Select DAY From Courses Where CRN = " + course1check;
		sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
		sqlite3_step(stmt);
		auto tempDays = sqlite3_column_text(stmt, 0);
		size_t s = sqlite3_column_bytes(stmt, 0);
		days1 = (s > 0 ? string((const char*)tempDays, s) : "");

		// Gets the start time of 'class 1'
		sql = "Select TIME1 From Courses Where CRN = " + course1check;
		sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
		sqlite3_step(stmt);
		time1start = sqlite3_column_int(stmt, 0);

		// Gets the end time of 'class 1'
		sql = "Select TIME2 From Courses Where CRN = " + course1check;
		sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
		sqlite3_step(stmt);
		time1end = sqlite3_column_int(stmt, 0);

		// Goes through the days that 'class 1' is taught
		// Iterates through it and adds it to vector dayCheck1
		vector<string> dayCheck1{};

		pos = 0;
		while ((pos = days1.find(space_delimiter)) != string::npos) {
			dayCheck1.push_back(days1.substr(0, pos));
			days1.erase(0, pos + space_delimiter.length());
		}

		// Goes through every day that 'class 1' is taught
		for (const auto& dayCheck : dayCheck1) {
			for (const auto& course2check : course) {
				// Checks to see if the current course being checked is the same as the original
				if (course2check != course1check) {
					// Checks to see if the course being checked occurs on the same day as the original course
					// If the courses are on the same day, gets the time it occurs
					sql = "SELECT TIME1 FROM COURSES WHERE DAY LIKE '%" + dayCheck + "%' AND CRN = " + course2check;
					//cout << sql << endl;
					sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
					sqlite3_step(stmt);
					time2start = sqlite3_column_int(stmt, 0);

					// Checks if the second courses start time is between the first courses start and end time
					if (time2start < time1end && time2start > time1start) {
						cout << "There is a time conflict between CRN " << course1check << " and " << course2check << endl;
						cout << "The conflict is on the following day: " << dayCheck << endl;
					}
				}
			}
		}		
	}

	sqlite3_close(db);
}