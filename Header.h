#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <sqlite3.h>
#include <cstdlib>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;
using std::vector; 
using std::istringstream;
using std::stringstream;

// Function Prototypes
int callback(void* data, int argc, char** argv, char** azColName);
