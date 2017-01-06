#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#define TMap std::map

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
	INVALID_PATH,//Path Valid
	INVALID_STATUS,//default
	INVALID_FORMAT,//Not Contain characters Valid
	NOT_CONTAIN_ONE_START, // Not Contain always one start
	NOT_CONTAIN_DELIVERY, // Not delivery poinst
	NOT_CONTAIN_PAKAGE, // No pakages for delivery
	WRONG_LENGTH_ROWS,//Row length valid
	INVALID_EXTENCION_FILE// Extencion equals txt
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
	TMap <char, bool> validCharacters;//List Character Valid

	bool isLengthValid(FString) const;
	bool isValidExtencion(FString) const;
	bool isPathFile(FString) const;
	bool isValidFormatMap(FString) const;
};