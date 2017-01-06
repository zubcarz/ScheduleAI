#pragma once

#include "FNavigationRobot.h"

//constructor
FNavigationRobot::FNavigationRobot()
{
	validCharacters['o'] = true;// Empty
	validCharacters['S'] = true;// Start
	validCharacters['X'] = true;// Wall
	validCharacters['E'] = true;// Delivery
	validCharacters[','] = true;// Separator
}

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
//TODO Optimize Method find Character
bool FNavigationRobot::isValidFormatMap(FString mapDocument) const
{
	TMap <char, bool> character = validCharacters;

	for (char letter : mapDocument) {
		if (!character[letter] && !isdigit((int)(letter))) {
			return false;
		}

			/*switch (letter)
			{
				case 'o':
					mapCount.empty++;
					break;
				case 'S':
					mapCount.start++;
					break;
				case 'X':
					mapCount.wall++;
					break;
				case 'E':
					mapCount.delivery++;
					break;
				case ',':
					//ignore
					break;
				default:
					mapCount.package++;
					break;
			}*/
		
	}


	return true;
}

bool FNavigationRobot::isLengthValid(FString mapDocument) const
{
	std::stringstream map(mapDocument);
	FString row;
	int sizeRow = 0;
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

bool FNavigationRobot::isPathFile(FString pathFile) const
{
	std :: ifstream file;
	file.open(pathFile.c_str());
	bool isOpen = isOpen = (file) ? true : false;
	file.close();
	return isOpen;
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
	int countPackage = std::count_if(mapDocument.begin(), mapDocument.end(), [](char i) {return isdigit((int)i);});
	if (countPackage > 0)
	{
		return true;
	}
	return false;
}
