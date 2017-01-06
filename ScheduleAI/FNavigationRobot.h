#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

#define TMap std::map

using FString = std::string;
using int32 = int;


struct MapInfo
{
	int32 cells = 0;
	int32 rows = 0;
	int32 column = 0;
	int32 empty = 0;
	int32 wall = 0;
	int32 package = 0;
	int32 start = 0;
	int32 delivery = 0;
};

enum class EMapStatus {
	OK,
	INVALID_PATH,//Path Valid
	INVALID_STATUS,//default
	INVALID_FORMAT,//Not Contain characters Valid
	INVALID_POINT_START, // Not Contain always one start
	NOT_CONTAIN_DELIVERY, // Not delivery poinst
	NOT_CONTAIN_PACKAGE, // No pakages for delivery
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
	bool isContainDelivery(FString )const;
	bool isValidStart(FString) const;
	bool isContainPackage(FString) const;
};