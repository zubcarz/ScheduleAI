#pragma once

#include <string>

using FString = std::string;
using int32 = int;

struct RobotCount
{
	int32 cells = 0;
	int32 score = 0;
	int32 time = 100;
};

enum class EMapStatus {
	OK,
	NOT_MAP,
	INVALID_PATH,
	INVALID_STATUS,
	WRONG_LENGTH_ROWS
};

class FNavigationRobot
{

public:
	//Constructor
	FNavigationRobot();

private:
	FString map;

};