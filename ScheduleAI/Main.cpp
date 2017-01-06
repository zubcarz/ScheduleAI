#pragma once

#include "main.h"

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
	FText pathFileMap = "";

	//Check Valid Map
	EMapStatus statusMap = EMapStatus::INVALID_STATUS; // status by default
	do {
		
		//Check Valid Path
		EMapStatus statusPath = EMapStatus::INVALID_STATUS;
		do {
			std::cout << " Enter path file to valid Map :";
			getline(std::cin, pathFileMap);
			statusPath = BCNavigation.checkPathValidity(pathFileMap);
			switch (statusPath)
			{
				case EMapStatus::INVALID_PATH:
					std::cout << " !!Error!!  Path File is invalid";
					break;
				case EMapStatus::INVALID_EXTENCION_FILE:
					std::cout << " !!Error!!  Your extencion file is not valid";
					break;
				default:
					std::cout << " Is Valid Path";
					break;
			}
			std::cout << std::endl;
	
		} while (statusPath != EMapStatus::OK);
		
		FString document = readText(pathFileMap);
		statusMap = BCNavigation.checkMapValidity(document);

		switch (statusMap)
		{
		case EMapStatus::INVALID_FORMAT:
			std::cout << "  !!Error!! Map contains invalid characters ";
			break;
		case EMapStatus::WRONG_LENGTH_ROWS:
			std::cout << " !!Error!! The map should be have rows of the same size";
			break;
		default:
			std::cout << " Is Valid Map";
			break;
		}

		std::cout << std::endl << std::endl;
	} while (statusMap != EMapStatus :: OK);
	std::cout << std::endl;
	return FText();
}

FText readText(FText path)
{

	std :: ifstream mapFile;
	mapFile.open(path);
	FString document;
	if (mapFile.is_open()) {
		while (!mapFile.eof()) {
			//write text in var
			FString line;
			getline(mapFile, line);
			document = document + line ;
		}
	}
	
	mapFile.close();
	return document;
}

bool askToRunSolutionAgain()
{
	std::cout << " Do you want to Run Solution again? Y/N : ";
	FText response = "";
	getline(std::cin, response);
	return (response[0] == 'Y' || response[0] == 'y') ? true : false;
	return false;
}
