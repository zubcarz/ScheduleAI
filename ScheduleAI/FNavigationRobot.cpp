#pragma once

#include "FNavigationRobot.h"

//constructor
FNavigationRobot::FNavigationRobot()
{
	reset();
}

//gets
MapInfo FNavigationRobot::getMapInfo() const{return mapInfo;}
VectorPos2D FNavigationRobot::getStartPosition() const{return startPosition;}
ArrayList FNavigationRobot::getPositionPackage() const{return positionPackage;}
ArrayList FNavigationRobot::getPositionPointsDelivery() const{return positionPointsDelivery;}


EMapStatus FNavigationRobot::checkMapValidity(FString mapDocument) const
{
	if (!isValidFormatMap(mapDocument))
	{
		return EMapStatus::INVALID_FORMAT;
	}
	else if (!isLengthValid(mapDocument))
	{
		return EMapStatus::WRONG_LENGTH_ROWS;
	}
	else if (!isContainDelivery(mapDocument))
	{
		return EMapStatus::NOT_CONTAIN_DELIVERY;
	}
	else if (!isContainPackage(mapDocument))
	{
		return EMapStatus::NOT_CONTAIN_PACKAGE;
	}
	else if (!isValidStart(mapDocument))
	{
		return EMapStatus::INVALID_POINT_START;
	}
	else
	{
		return EMapStatus::OK;
	}
}

EMapStatus FNavigationRobot::checkPathValidity(FString pathFile) const
{
	if (!isPathFile(pathFile))
	{
		return EMapStatus::INVALID_PATH;
	}
    else if(!isValidExtencion(pathFile))
	{
		return EMapStatus::INVALID_EXTENCION_FILE;
	}
	else
	{
		return EMapStatus::OK;
	}
}

void FNavigationRobot::reset()
{
	mapDocument = "";
	
	clearInfo();

	positionPackage.clear();
	positionPointsDelivery.clear();

	validCharacters['o'] = true;// Empty
	validCharacters['S'] = true;// Start
	validCharacters['X'] = true;// Wall
	validCharacters['E'] = true;// Delivery
	validCharacters[','] = true;// Separator
}

void FNavigationRobot::setMapDocument(FString mapDocument)
{
	this->mapDocument = mapDocument;
}

Matriz FNavigationRobot::builderNavMap()
{

	if (!mapDocument.empty()) {
		std::stringstream map(mapDocument);
		FString row;
		int32 sizeDocument = mapDocument.length();
		int32 rowSize = (int32)getline(map, row, ',').tellg() - 1;
		int32 columnSize = sizeDocument / rowSize;

		mapInfo.rowSize = rowSize;
		mapInfo.columnSize = columnSize;
		mapInfo.countCells = mapInfo.rowSize * mapInfo.columnSize;

		Matriz mapNav;

		//create Matrix
		int32 countPosRow = 0;
		 do{
			int32 countPosColumn = 0;
			std::vector<int> rowNav;
			for (auto letter : row) {
				VectorPos2D cellPosition = { countPosRow,countPosColumn };

				if (letter == 'X') {
					rowNav.push_back(100000);
				}
				else {
					rowNav.push_back(0);
				}

				switch (letter)
				{
					case 'o':	
						mapInfo.countEmpty++;
						break;
					case 'S':
						startPosition = cellPosition;
						mapInfo.countStart++;
						break;
					case 'X':
						mapInfo.countWall++;
						break;
					case 'E':
						positionPointsDelivery.push_back(cellPosition);
						mapInfo.countDelivery++;
						break;
					default:
						if (isdigit((int)letter)) {
							positionPackage.push_back(cellPosition);
							mapInfo.countPackage++;
						}
						break;
				}
				countPosColumn++;
			}
			mapNav.push_back(rowNav);
			countPosRow++;
		 } while (getline(map, row, ','));
		 navigationMap = mapNav;
		 return mapNav;
	}
	return Matriz();
}

//TODO Optimize Method find Character
bool FNavigationRobot::isValidFormatMap(FString mapDocument) const
{
	TMap <char, bool> character = validCharacters;

	for (char letter : mapDocument) {
		if (!character[letter] && !isdigit((int32)(letter))) {
			return false;
		}
	}
	return true;
}

bool FNavigationRobot::isPathFile(FString pathFile) const
{
	std::ifstream file;
	file.open(pathFile.c_str());
	bool isOpen = isOpen = (file) ? true : false;
	file.close();
	return isOpen;
}

bool FNavigationRobot::isLengthValid(FString mapDocument) const
{
	std::stringstream map(mapDocument);
	FString row;
	int32 sizeRow = 0;
	while (getline(map, row, ','))
	{
		if (sizeRow == 0) {
			sizeRow = row.length();
		}else if (sizeRow != row.length()) {
			return false;
		}
	}
	return true;
}

bool FNavigationRobot::isValidExtencion(FString pathFile) const
{
	
	if (pathFile.substr(pathFile.find_last_of(".") + 1) == "txt") {
		return true;
	}
	
	return false;
}

bool FNavigationRobot::isContainDelivery(FString mapDocument) const
{
	if (mapDocument.find('E') != std::string::npos)
	{
		return true;
	}
	return false;
}

bool FNavigationRobot::isValidStart(FString mapDocument) const
{
	int32 countStart = std::count(mapDocument.begin(), mapDocument.end(), 'S');
	if (countStart != 1)
	{
		return false;
	}
	return true;
}

bool FNavigationRobot::isContainPackage(FString mapDocument) const
{
	int32 countPackage = std::count_if(mapDocument.begin(), mapDocument.end(), [](char i) {return isdigit((int32)i);});
	if (countPackage > 0)
	{
		return true;
	}
	return false;
}

void FNavigationRobot::clearInfo()
{
	mapInfo.countCells = 0;
	mapInfo.rowSize = 0;
	mapInfo.columnSize = 0;

	mapInfo.countEmpty = 0;
	mapInfo.countWall = 0;
	mapInfo.countPackage = 0;
	mapInfo.countStart = 0;
	mapInfo.countDelivery = 0;
}

void FNavigationRobot::sortPointsDelivery()
{
	ArrayList sortDelivery;
	ArrayList snapshotPositionDeliverity = positionPointsDelivery;
		
	do {
		int minorRegister;
		int minorDistance = pow(10, 7);
		for (int i = 0; i < snapshotPositionDeliverity.size(); i++) {
			int distance = getDistanceDocument(snapshotPositionDeliverity[i], startPosition);
				//abs(snapshotPositionDeliverity[i][1] - startPosition[1]) + abs(snapshotPositionDeliverity[i][0] - startPosition[0]);
			if (distance < minorDistance) {
				minorDistance = distance;
				minorRegister = i;
			}
		}
		sortDelivery.push_back(snapshotPositionDeliverity[minorRegister]);

		snapshotPositionDeliverity.erase(snapshotPositionDeliverity.begin()+ (minorRegister));

	} while (snapshotPositionDeliverity.size() != 0);

	positionPointsDelivery = sortDelivery;
}

void FNavigationRobot::sortPointsPackage()
{
	ArrayList sortPackage;
	ArrayList snapshotPackage = positionPackage;

	do {
		int minorRegister;
		int minorDistance = pow(10, 8);
		int deliveryTo;
		int distance = pow(10, 8);

		for (int i = 0; i < snapshotPackage.size(); i++) {
			for (int j = 0; j < positionPointsDelivery.size(); j++) {
				int distanceToDelivery = getDistanceDocument(snapshotPackage[i], positionPointsDelivery[j]);

				if (distanceToDelivery < distance) {
 					distance = distanceToDelivery;
					deliveryTo = j;
				}
			}

			if (distance < minorDistance) {
				minorDistance = distance;
				minorRegister = i;
			}
		}
		
		sortPackage.push_back(snapshotPackage[minorRegister]);

		std::cout << "POINT CLOSE TO DELIVERY" << std::endl;
		std::cout << "Send From : " << sortPackage.size() - 1 
			      << " (" << snapshotPackage[minorRegister][0] << ","<< snapshotPackage[minorRegister][1] <<")"
				  << ", Distance :" << minorDistance 
				  << ", Send To ->" << deliveryTo << std::endl;

		deliveryAssignment.push_back(deliveryTo);
		distanceToDelivery.push_back(minorDistance);

		snapshotPackage.erase(snapshotPackage.begin() + (minorRegister));

	} while (snapshotPackage.size() != 0);
	std::cout << std::endl;

	positionPackage = sortPackage;
}

int FNavigationRobot::getDistanceDocument(VectorPos2D startPosition, VectorPos2D goalPosition)
{
	int distance = 0;

	int distanceYElbowUp = 0;
	int distanceYElbowDown = 0;
	int distanceXElbowUp = 0;
	int distanceXElbowDown = 0;
	int distanceElbowDown = 0;
	int distanceElbowUp= 0;

	if (startPosition[0] != goalPosition[0]) {
		int moveXU = startPosition[0];
		do {
			distanceYElbowUp = distanceYElbowUp + navigationMap[moveXU][startPosition[1]] + 1;
			if (startPosition[0] < goalPosition[0]) {
				moveXU++;
			}
			else {
				moveXU--;
			}
		} while (moveXU != goalPosition[0]);

		int moveXD = startPosition[0];
		do {
			distanceYElbowDown = distanceYElbowDown + navigationMap[moveXD][goalPosition[1]] + 1;
			if (startPosition[0] < goalPosition[0]) {
				moveXD++;
			}
			else {
				moveXD--;
			}
		} while (moveXD != goalPosition[0]);
	}

	if (startPosition[1] != goalPosition[1]) {
		int moveYU = startPosition[1];
		int moveYD = startPosition[1];

		do {
			distanceXElbowUp = distanceXElbowUp + navigationMap[goalPosition[0]][moveYU] + 1 ;
			if (startPosition[1] < goalPosition[1]) {
				moveYU++;
			}
			else {
				moveYU--;
			}
		} while (moveYU != goalPosition[1]);

		do {
			distanceXElbowDown = distanceXElbowDown + navigationMap[startPosition[0]][moveYD] + 1;
			if (startPosition[1] < goalPosition[1]) {
				moveYD++;
			}
			else {
				moveYD--;
			}
		} while (moveYD != goalPosition[1]);
	}

	distanceElbowUp = distanceYElbowUp + distanceXElbowUp;
	distanceElbowDown = distanceYElbowDown + distanceXElbowDown;

	if (distanceElbowDown < distanceElbowUp) {
		distance = distanceElbowDown - navigationMap[startPosition[0]][goalPosition[1]];
	}
	else {
		distance = distanceElbowUp - navigationMap[goalPosition[0]][startPosition[1]];
	}

	return distance;
}

int FNavigationRobot::getAssignment()
{
	return 0;
}

ArrayList FNavigationRobot::getDestinations()
{
	pointsOfDestination.clear();

	sortPointsDelivery();
	sortPointsPackage();

	/*ArrayList positionPackage;
	ArrayList positionPointsDelivery;
	Matriz navigationMap;
	ArrayList PointsOfDestination;
	std::vector<int> deliveryAssignment;
	std::vector<int> valueAssignment;
	std::vector<int> distanceToDelivery;*/
	/*
	for (int i = 0; i < positionPackage.size(); i++) {
		pointsOfDestination.push_back(positionPackage[i]);
		pointsOfDestination.push_back(positionPointsDelivery[deliveryAssignment[i]]);
	}*/

	for (int i = 0; i < positionPointsDelivery.size(); i++) {
		for (int j = 0; j < positionPackage.size(); j++) {
			if (deliveryAssignment[i] == i) {
				pointsOfDestination.push_back(positionPackage[j]);
				pointsOfDestination.push_back(positionPackage[i]);
			}
		}

	}
	

	return pointsOfDestination;
}
