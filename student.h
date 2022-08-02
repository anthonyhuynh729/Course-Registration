#pragma once
#include "user.h"
class student :
    public user
{
public:
    student(string first, string last, string ID);

    void setAttributes(string fName, string lName, string ID);
    // Student class has four methods
    void addCourse(string ID, string CRNS);

    void removeCourse(string ID, string CRNS);

    void printSchedule(string ID);

    void checkConflicts(string ID);
};

