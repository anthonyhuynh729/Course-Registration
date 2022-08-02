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

void admin::addUser() // Adds a user with first name, last name, and ID
{
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;

	// Variables for all Users
	int ID = 0;
	string fname;
	string lname;
	string email;
	int userType;

	// Variables for admins and instructors
	string title;
	string office;

	// Variables for instructors
	int hireyear;
	string dept;

	// Variables for students
	int gradyear;
	string major;

	cout << "What type of user is being added?" << endl;
	cout << "1. Admin\n2. Instructor\n3. Student" << endl;
	cin >> userType;

	cout << "Enter the first name: ";
	cin >> fname;
	cout << "Enter the last name: ";
	cin >> lname;
	email = lname + fname[0];
	// Makes email all lowercase to match other emails
	std::transform(email.begin(), email.end(), email.begin(),
		[](unsigned char c) { return std::tolower(c); });
	cout << "User's Email is " << email << endl;

	// Depending on user type asks for different variables
	switch (userType) {
	case 1:
		cout << "Enter their Title: ";
		cin >> title;
		cout << "Enter their Office: ";
		cin.ignore();
		getline(cin, office);

		// Gets the highest ID from the admin table and adds 1 to it
		sql = "Select MAX(ID) FROM ADMIN";
		sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
		sqlite3_step(stmt);
		ID = sqlite3_column_int(stmt, 0);
		ID = ID + 1;

		// Creates the string and then executes it
		sql = "INSERT INTO ADMIN VALUES(" + to_string(ID) + ", '" + fname + "', '" + lname + "', " + title + ", '" + office + "', '" + email + "');";
		exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

		// Outputs whether the course was successfully added
		if (exit != SQLITE_OK) {
			std::cerr << "Error Adding Admin" << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Admin Added Successfully" << endl;
		break;

	case 2:
		cout << "Enter their Title: ";
		cin >> title;
		cout << "Enter their Office: ";
		cin.ignore();
		getline(cin, office);
		cout << "Enter their hire year: ";
		cin >> hireyear;
		cout << "Enter their department: ";
		cin.ignore();
		getline(cin, dept);

		// Gets the highest ID from the instructor table and adds 1 to it
		sql = "Select MAX(ID) FROM INSTRUCTOR";
		sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
		sqlite3_step(stmt);
		ID = sqlite3_column_int(stmt, 0);
		ID = ID + 1;

		// Creates the string and then executes it
		sql = "INSERT INTO INSTRUCTOR VALUES(" + to_string(ID) + ", '" + fname + "', '" + lname + "', " + title + ", " + to_string(hireyear) + ", '" + dept + "', '" + email + "');";
		exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
		

		// Outputs whether the course was successfully added
		if (exit != SQLITE_OK) {
			std::cerr << "Error Adding Instructor" << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Instructor Added Successfully" << endl;
		break;
	case 3:
		cout << "Enter their graduation year: ";
		cin >> gradyear;
		cout << "Enter their major: ";
		cin.ignore();
		getline(cin, major);

		// Gets the highest ID from the student table and adds 1 to it
		sql = "Select MAX(ID) FROM STUDENT";
		sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
		sqlite3_step(stmt);
		ID = sqlite3_column_int(stmt, 0);
		ID = ID + 1;

		// Creates the string and then executes it
		sql = "INSERT INTO STUDENT VALUES(" + to_string(ID) + ", '" + fname + "', '" + lname + "', " + to_string(gradyear) + ", '" + major + "', '" + email + "', NULL);";
		exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);

		// Outputs whether the course was successfully added
		if (exit != SQLITE_OK) {
			std::cerr << "Error Adding Student" << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Student Added Successfully" << endl;
		break;
	}


}

void admin::removeUser() // Removes a user, requires ID
{
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;

	int ID;
	int userType;

	cout << "Enter ID of the user you would like to remove: ";
	cin >> ID;
	userType = ID;
	// Gets highest digit from ID
	// Admin IDs start with 3, Instructor IDs start with 2, Student IDs start with 1
	while (userType >= 10) {
		userType = userType / 10;
	}
	// Depending on highest digit goes to corresponding table
	// Deletes the entry that has the same ID
	switch (userType) {
	case 1:
		// Creates the string and then executes it
		sql = "DELETE FROM STUDENT WHERE ID = " + to_string(ID);
		exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);


		// Outputs whether the course was successfully added
		if (exit != SQLITE_OK) {
			std::cerr << "Error Deleting Student" << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Student Deleted Successfully" << endl;
		break;
	case 2:
		// Creates the string and then executes it
		sql = "DELETE FROM INSTRUCTOR WHERE ID = " + to_string(ID);
		exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);


		// Outputs whether the course was successfully added
		if (exit != SQLITE_OK) {
			std::cerr << "Error Deleting Instructor" << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Instructor Deleted Successfully" << endl;
		break;
	case 3:
		// Creates the string and then executes it
		sql = "DELETE FROM ADMIN WHERE ID = " + to_string(ID);
		exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);


		// Outputs whether the course was successfully added
		if (exit != SQLITE_OK) {
			std::cerr << "Error Deleting Admin" << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Admin Deleted Successfully" << endl;
		break;
	}

}

void admin::linkUserCourse(){
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;

	int userType;
	string tableName;
	int ID;
	string CRN;
	string tempCRN;

	// Asks admin for user type
	cout << "What type of user is being added?" << endl;
	cout << "1. Instructor\n2. Student" << endl;
	cin >> userType;

	cout << "What is their ID : ";
	cin >> ID;

	cout << "What CRN would you like to add: ";
	cin >> CRN;

	switch (userType) {
	case 1:
		tableName = "INSTRUCTOR";
		break;
	case 2:
		tableName = "STUDENT";
		break;
	}

	// Creates the string and then executes it
	sql = "SELECT COURSES FROM " + tableName + " WHERE ID = " + to_string(ID);
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	auto first = sqlite3_column_text(stmt, 0);
	size_t s = sqlite3_column_bytes(stmt, 0);
	tempCRN = (s > 0 ? string((const char*)first, s) : "");

	cout << tempCRN << endl;
	CRN = tempCRN + " " + CRN;
	cout << CRN << endl;

	sql = "UPDATE " + tableName + " SET COURSES = '" + CRN + "' WHERE ID = " + to_string(ID);;
	exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);


	// Outputs whether the course was successfully added
	if (exit != SQLITE_OK) {
		std::cerr << "Error Linking Course" << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Course Linked Successfully" << endl;

}

void admin::unlinkUserCourse() {
	// Opens the users database
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("Users.db", &db);
	string sql;
	int exit;
	char* messageError;

	int userType;
	string tableName;
	int ID;
	string CRN;
	string tempCRN;

	cout << "What type of user is being added?" << endl;
	cout << "1. Instructor\n2. Student" << endl;
	cin >> userType;

	cout << "What is their ID : ";
	cin >> ID;

	cout << "What CRN would you like to remove: ";
	cin >> CRN;

	switch (userType) {
	case 1:
		tableName = "INSTRUCTOR";
		break;
	case 2:
		tableName = "STUDENT";
		break;
	}

	// Creates the string and then executes it
	sql = "SELECT COURSES FROM " + tableName + " WHERE ID = " + to_string(ID);
	sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	auto first = sqlite3_column_text(stmt, 0);
	size_t s = sqlite3_column_bytes(stmt, 0);
	tempCRN = (s > 0 ? string((const char*)first, s) : "");

	// Checks to see if the CRN exists inside of the current CRNS
	string::size_type i = tempCRN.find(CRN);

	if (i != string::npos) {
		tempCRN.erase(i, CRN.length());
		sql = "UPDATE " + tableName + " SET COURSES = '" + tempCRN + "' WHERE ID = " + to_string(ID);;
		exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError);
		cout << "CRN has been unlinked" << endl;
	}
	else {
		cout << "CRN was not originally linked." << endl;
		cout << "Aborted Action" << endl;
	}
}
