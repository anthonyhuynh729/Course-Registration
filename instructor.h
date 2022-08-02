#pragma once
#include "user.h"
class instructor :
    public user
{
public:
    instructor(string first, string last, string ID);
    void setAttributes(string fName, string lName, string ID);
    // Three methods for instructor class
    void addCourse(string ID, string CRNS);
    void removeCourse(string ID, string CRNS);
    void printSchedule(string ID);
    void printCourseRoster(string ID);
    void courseSearch();
};

