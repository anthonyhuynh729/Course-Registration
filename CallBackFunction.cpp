#pragma once
#include "Header.h"

int callback(void* data, int argc, char** argv, char** azColName)
{

	for (int i = 0; i < argc; i++) {
		cout << azColName[i] << ": " << argv[i] << endl;
	}

	printf("\n");
	return 0;
}
