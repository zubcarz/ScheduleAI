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
	INVALID_PATH,
	INVALID_STATUS,//default
	INVALID_FORMAT,
	WRONG_LENGTH_ROWS,
	INVALID_EXTENCION_FILE
};

class FNavigationRobot
{

public:
	//Constructor
	FNavigationRobot();
	EMapStatus checkMapValidity(FString) const;
	EMapStatus checkPathValidity(FString) const;

private:
	FString map;
	bool isMap(FString) const;
	bool isLengthValid(FString) const;
	bool isValidExtencion(FString) const;
	bool isPathFile(FString) const;

};