#pragma once

#include "main.h"

FNavigationRobot BCNavigation;

int32 main()
{
	do {
		welcomeGame(); 
		playSolution();
		BCNavigation.reset();
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
	//Cycle
	//create grafo
	//send vetor position grafo por grafo
	FText validMap =  getValidMap();
	FMatriz navigationMap = BCNavigation.builderNavMap();

	BCNavigation.getDestinations();

	printInfoMap();
	printInfoNavigationMap(navigationMap);

	FPathFindingA BCPathFinder(navigationMap, BCNavigation.getMapInfo().rowSize, BCNavigation.getMapInfo().columnSize);
	bool isShowStepByStep = askToShowStepBystep();
	bool hasLoad = false;
	BCPathFinder.moveTo(BCNavigation.getStartPosition(),BCNavigation.getPositionPackage()[0], hasLoad,isShowStepByStep);

	//class navigation 
		//definir entrega
		//definir recojida
		//trayectoria (inicial, final)
		//score
		//Comandos del camino
		//print step by step 
		
}

FText getValidMap()
{
	FText pathFileMap = "";
	FText document = "";
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
		
		document = readText(pathFileMap);
		statusMap = BCNavigation.checkMapValidity(document);

		switch (statusMap)
		{
		case EMapStatus::INVALID_FORMAT:
			std::cout << "  !!Error!! Map contains invalid characters ";
			break;
		case EMapStatus::WRONG_LENGTH_ROWS:
			std::cout << " !!Error!! The map should be have rows of the same size";
			break;
		case EMapStatus::NOT_CONTAIN_DELIVERY:
			std::cout << " !!Error!! The map must have at least one delivery point";
			break;
		case EMapStatus::NOT_CONTAIN_PACKAGE:
			std::cout << " !!Error!! The map must have at least one package";
			break;
		case EMapStatus::INVALID_POINT_START:
			std::cout << " !!Error!! The map does not contain a starting point or contains more than one";
			break;
		default:
			BCNavigation.setMapDocument(document);
			std::cout << " Is Valid Map"<< std::endl;
			break;
		}
		std::cout << std::endl;
	} while (statusMap != EMapStatus :: OK);

	return document;
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
}

void printInfoMap()
{

	MapInfo mapInfo = BCNavigation.getMapInfo();
	std::cout << "BASE INFO" << std::endl;
		std::cout << "  Count Cells: " << mapInfo.countCells << std::endl;
		std::cout << "  Row size: " << mapInfo.rowSize <<  std::endl;
		std::cout << "  Column Size: " << mapInfo.columnSize << std::endl;
		std::cout << "  Count Empty: " << mapInfo.countEmpty << std::endl;
		std::cout << "  Count Wall: " << mapInfo.countWall << std::endl;
		std::cout << "  Count Package: " << mapInfo.countPackage << std::endl;
		std::cout << "  Count Start: " << mapInfo.countStart << std::endl;
		std::cout << "  Count Delivery: " << mapInfo.countDelivery << std::endl << std::endl;
	
	std::cout << "STAR POSITION" << std::endl;
		std::cout << "  Pos : (" << BCNavigation.getStartPosition()[0] << "," << BCNavigation.getStartPosition()[1] << ")" << std::endl;
	std::cout << std::endl;

	std::cout << "POSITION DELIVERY" << std::endl;
		for (auto deliveryPosition : BCNavigation.getPositionPointsDelivery()) {
			std::cout << "  Pos : (" << deliveryPosition[0] << "," << deliveryPosition[1] <<")"<< std::endl;
		}
	std::cout << std::endl;

	std::cout << "POSITION PACKAGE" << std::endl;
		for (auto packagePosition : BCNavigation.getPositionPackage()) {
			std::cout << "  Pos : (" << packagePosition[0] << "," << packagePosition[1] << ")" << std::endl;
		}
	std::cout << std::endl;

	//std::cout << std::get<0>(BCNavigation.positionPackage[1]) << std::endl; */
}

void printInfoNavigationMap(Matriz navigationMap)
{
	std::cout << "Navigation Map" << std::endl;
	int countRow = 0;
	for (auto row : navigationMap) {
		int countColumn = 0;
		for (auto cell : row) {
			int sizeCell = std::to_string(cell).length();
			FText space = "";
			for (int i = 0 ; i<8-sizeCell; i++) {
				space = space + " ";
			}
			std::cout << space;
			if (BCNavigation.getStartPosition()[0] == countRow && BCNavigation.getStartPosition()[1] == countColumn) {
				std::cout << "S" ;
			}
			else {
				std::cout << cell;
			}
			
			countColumn++;
		}
		countRow++;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool askToShowStepBystep()
{
	std::cout << " Do You want to see step by step ? Y/N : ";
	FText response = "";
	getline(std::cin, response);
	return (response[0] == 'Y' || response[0] == 'y') ? true : false;
}
