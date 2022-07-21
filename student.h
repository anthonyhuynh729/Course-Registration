#pragma once
#include "user.h"
class student :
    public user
{
public:
    student(string first, string last, string ID);

    void setAttributes(string fName, string lName, string ID);
    // Student class has three methods
    void courseSearch();

    void addCourse(string ID, string CRNS);

    void removeCourse(string ID, string CRNS);

    void printSchedule();
};

