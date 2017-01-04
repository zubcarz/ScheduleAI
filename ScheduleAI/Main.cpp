#pragma once

#include <iostream>
#include <string>
#include "main.h"
#include "FNavigationRobot.h"

using FText = std::string;
using int32 = int;

FNavigationRobot BCNavigation;

int32 main()
{
	do {
		welcomeGame(); 
		playSolution();
	} while (askToRunSolutionAgain());

	return 0; //exit game
}


void welcomeGame()
{
	std::cout << "Welcome to ScheduleAI.\n" << std::endl;
	return;
}

void playSolution()
{
	getValidMap();
}

FText getValidMap()
{
	FText pathFlieMap = "";

	//Check Valid Map
	EMapStatus statusMap = EMapStatus::INVALID_STATUS; // status by default
	do {
		
		//Check Valid Path
		EMapStatus statusPath = EMapStatus::INVALID_STATUS;
		do {
			std::cout << " Enter path file to valid Map :";
			getline(std::cin, pathFlieMap);
			statusPath = BCNavigation.checkPathValidity(pathFlieMap);
			switch (statusPath)
			{
				case EMapStatus::INVALID_PATH:
					std::cout << " Please enter a Path File Valid";
					break;
				case EMapStatus::INVALID_EXTENCION_FILE:
					std::cout << " Yor extencion file is not valid";
					break;
				default:
					std::cout << " Is Valid Path";
					break;
			}
			std::cout << std::endl << std::endl;
		} while (statusPath != EMapStatus::OK);

		statusMap = BCNavigation.checkMapValidity(pathFlieMap);
	
	} while (statusMap != EMapStatus :: OK);
	std::cout << std::endl;
	return FText();
}

bool askToRunSolutionAgain()
{
	std::cout << " Do you want to Run Solution again? Y/N : ";
	FText response = "";
	getline(std::cin, response);
	return (response[0] == 'Y' || response[0] == 'y') ? true : false;
	return false;
}
