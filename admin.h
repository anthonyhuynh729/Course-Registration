#pragma once
#include "user.h"
class admin :
    public user
{
public:
    admin(string first, string last, string ID);
    void setAttributes(string fName, string lName, string ID);

    // 7 Methods exclusive to admin class
    void addCourse(string ID, string courseName, string dept, int time, string days, string semester, int year, int credits);

    void removeCourse(string ID);

    void addUser(string firstName, string lastName, string userID);

    void removeUser(string firstName, string lastName, string userID);

    void addStudent(string firstName, string lastName, string userID, string courseName);

    void removeStudent(string firstName, string lastName, string userID, string courseName);

    void searchRosters();


};

