#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <iterator>
#include <array>


#define TMap std::map

using FString = std::string;
using int32 = int;
using VectorPos2D = std::array<double, 2>;
using ArrayList = std::vector<VectorPos2D>;
using Matriz = std::vector<std::vector<int>>;

struct MapInfo
{
	//map info
	int32 countCells = 0;
	int32 rowSize = 0;
	int32 columnSize = 0;

	//cells info
	int32 countEmpty = 0;
	int32 countWall = 0;
	int32 countPackage = 0;
	int32 countStart = 0;
	int32 countDelivery = 0;
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
	MapInfo getMapInfo() const;
	VectorPos2D getStartPosition() const;
	ArrayList getPositionPackage() const;
	ArrayList getPositionPointsDelivery() const;

	void reset();
	void setMapDocument(FString);
	Matriz builderNavMap(); // get Matriz wall 
						  // set properties
						 // set points package 
						// set points delivery
	
private:
	VectorPos2D startPosition;
	ArrayList positionPackage;//add reset
	ArrayList positionPointsDelivery; //add reset

	ArrayList PointsOfDestination; //sorted list by destination points

	FString mapDocument;
	MapInfo mapInfo;
	TMap <char, bool> validCharacters;//List Character Valid

	bool isLengthValid(FString) const;
	bool isValidExtencion(FString) const;
	bool isPathFile(FString) const;
	bool isValidFormatMap(FString) const;
	bool isContainDelivery(FString )const;
	bool isValidStart(FString) const;
	bool isContainPackage(FString) const;

	void clearInfo();
};