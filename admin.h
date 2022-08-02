#pragma once
#include "user.h"
class admin :
    public user
{
public:
    admin(string first, string last, string ID);
    void setAttributes(string fName, string lName, string ID);

    // 6 Methods exclusive to admin class
    void addCourse(string ID, string courseName, string dept, int time, string days, string semester, int year, int credits);

    void removeCourse(string ID);

    void addUser();

    void removeUser();

    void linkUserCourse();

    void unlinkUserCourse();

};

