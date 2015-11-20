
#ifndef ENUMS_H
#define ENUMS_H

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;


enum ErrorCodes{
	SUCCESS = 0,
	QUIT = 1,
	INPUT_NOT_VALID = 2,
	DRAW_GAME = 3,
	QUIT_GAME = 4,
	FAILURE = 5,
};

//to be used instead of hard coding array indices for argv
enum ArrayIndices{
	FILE_NAME = 0,
	GAME_NAME = 1,
	MAX_COMMANDS = 2,
	OPTIONAL_1 = 3,
	OPTIONAL_2 = 4,
};


#endif // ENUMS_H // 