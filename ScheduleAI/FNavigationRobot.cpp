#pragma once

#include "FNavigationRobot.h"
#include <map>
#include <iostream>
#include <fstream>
#define TMap std::map


FNavigationRobot::FNavigationRobot()
{
}

EMapStatus FNavigationRobot::checkMapValidity(FString) const
{
	return EMapStatus();
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

bool FNavigationRobot::isMap(FString) const
{
	return false;
}

bool FNavigationRobot::isLengthValid(FString) const
{
	return false;
}

bool FNavigationRobot::isPathFile(FString pathFile) const
{
	std :: ifstream infile;
	infile.open(pathFile.c_str());
	return (infile) ? true : false;
	//infile.close();
}

bool FNavigationRobot::isValidExtencion(FString pathFile) const
{
	
	if (pathFile.substr(pathFile.find_last_of(".") + 1) == "txt") {
		return true;
	}
	
	return false;
}
