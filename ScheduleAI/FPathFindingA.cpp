#include "FPathFindingA.h"

//Constructors
FPathFindingA::FPathFindingA()
{
	reset();
}

FPathFindingA::FPathFindingA(Matriz mapNavigation, int numberofRow, int numberOfColumn)
{
	reset();
	currentAngle = 0; // Increases clockwise
	this->mapNavigation = mapNavigation;
	snapshotMapNavigation = mapNavigation;

	this ->numberofRow = numberofRow;
	this->numberOfColumn = numberOfColumn;
}

FString FPathFindingA::moveTo(VectorPos2D posStart, VectorPos2D posEnd, bool hasLoad, bool isShowStepByStep)
{
	this -> posStart = posStart;
	this->posEnd = posEnd;
	FString commandsNavigation;

	/*bool isRigth = isRigthDirection();
	if (isRigth) {
		posCheckPosition.erase("West");
	}
	else {
		posCheckPosition.erase("East");
	}*/

	VectorPos2D currentPosition = posStart;
	ArrayList solutionNavigation;
	solutionNavigation.push_back(posStart);
	FString previousDirection = "";

	while (currentMoves != allowMoves && currentPosition != posEnd) {
		TMap <FString, VectorPos2D> validPosition = validPositiontoEvaluate(currentPosition, previousDirection);
		FString nextDirection = "";
		int minorheuristic = 100000;

		for (TMap <FString, VectorPos2D>::iterator iter = validPosition.begin(); iter != validPosition.end(); ++iter)
		{
			
			VectorPos2D posEvualuate = iter->second;
			int rowEvualate = currentPosition[0] + posEvualuate[0];
			int columnEvualate = currentPosition[1] + posEvualuate[1];
			if (mapNavigation[rowEvualate][columnEvualate] != 100000) {
				int heuristic = getDistance({ (double)rowEvualate, (double)columnEvualate })*gain;
				mapNavigation[rowEvualate][columnEvualate] = heuristic;

				if (minorheuristic > heuristic) {
					minorheuristic = heuristic;
					nextDirection = iter->first;
				}
			}
			
		}

		previousDirection = nextDirection;
		
		currentMoves++;
		currentPosition = { currentPosition[0] + (validPosition[nextDirection])[0], currentPosition[1] + (validPosition[nextDirection])[1]};
		std::cout << "Current Position : "<< "(" << currentPosition[0] << "," << currentPosition[1] << ")" << std::endl;

		if (isShowStepByStep) {
			printNavigationMap(currentPosition, posEnd);
			_sleep(500); //deley 0.5 second
		}
		solutionNavigation.push_back(currentPosition);
	}
	
	/*if (isShowStepByStep) {
		printArrayList("Navigation Path", solutionNavigation);
	}*/

	commandsNavigation = builderCommand(solutionNavigation, hasLoad);

	return commandsNavigation;
}

void FPathFindingA::printNavigationMap(VectorPos2D currentPosition, VectorPos2D goalPosition)
{
	
    std::cout << "Navigation Map" << std::endl;
	int countRow = 0;
	for (auto row : mapNavigation) {
		int countColumn = 0;
		for (auto cell : row) {
			int sizeCell = std::to_string(cell).length();
			FString space = "";
			for (int i = 0; i<8 - sizeCell; i++) {
				space = space + " ";
			}
			if (posStart[0] == countRow && posStart[1] == countColumn) {
				std::cout << "       ";
				std::cout << "S";
			}
			else if (countRow == currentPosition[0] && countColumn == currentPosition[1]){
				std::cout << "       ";
				std::cout << "C"; //Position Robot
			}
			else if (goalPosition[0] == countRow && goalPosition[1] == countColumn) {
				std::cout << "       ";
				std::cout << "G";//Goal position
			}
			else {
				std::cout << space;
				std::cout << cell;
			}

			countColumn++;
		}
		countRow++;
		std::cout << std::endl;
	}
	std::cout << std::endl; 
}

void FPathFindingA::printArrayList(FString message, ArrayList list)
{
	std::cout << message << std::endl;
	for (auto item : list) {
		std::cout << "  Pos : (" << item[0] << "," << item[1] << ")" << std::endl;
	}
	std::cout << std::endl;
}

bool FPathFindingA::isFinishMoves()
{
	return false;
}

void FPathFindingA::reset()
{
	allowMoves = 100;
	gain = 10;
	currentMoves = 0;
	
	resetMapNavigation();

	posCheckPosition["Nort"]  = { -1, 0 };
	posCheckPosition["East"] = { 0, 1 };
	posCheckPosition["South"] = { 1, 0 };
	posCheckPosition["West"]  = { 0, -1 };

	movesValid["Left"] = "I";
	movesValid["Rigth"] = "D";
	movesValid["Avance"] = "A";
	movesValid["AvanceTwice"] = "F";
	movesValid["Pick"] = "R";
	movesValid["Deliver"] = "E";
}

int FPathFindingA::getDistance(VectorPos2D evaluatePosition) const
{
	
	int disY =  abs(posEnd[1] - evaluatePosition[1]);
	int disX = abs(posEnd[0] - evaluatePosition[0]);
	int distance = disY + disX;

	return distance;
}

FString FPathFindingA::builderCommand(ArrayList solutionNavigation, bool hasLoad)
{
	std::cout << "# iter : " << solutionNavigation.size() << std::endl;
	FString commands = "";

	for (int i = 0; i < (solutionNavigation.size() - 1) ; i++) {
		
		int nextAngle = getNextAngle(solutionNavigation[i], solutionNavigation[i + 1]);

		while (currentAngle != nextAngle)
		{
		
			if (nextAngle>currentAngle) {
				currentAngle += 90;
				commands = commands + movesValid["Rigth"];
			}
			else if(nextAngle<currentAngle){
				currentAngle -= 90;
				commands = commands + movesValid["Left"];
			}
		}
		
		
		if (hasLoad) {
			if (nextAngle == currentAngle) {
				commands = commands + movesValid["Avance"];
			}
		}
		else {
			if (i < (solutionNavigation.size() - 2)) {
				int nextNextAngle = getNextAngle(solutionNavigation[i+1], solutionNavigation[i + 2]);
				//std::cout << "current  : " << currentAngle << " Next : " << nextAngle << " NextNext : "<< nextNextAngle <<std::endl;

				if (currentAngle == nextAngle && currentAngle == nextNextAngle) {
					commands = commands + movesValid["AvanceTwice"];
					i++;
				}else if (currentAngle == nextAngle) {
						commands = commands + movesValid["Avance"];
					}
     			}
			else {
				if (currentAngle == nextAngle) {
					commands = commands + movesValid["Avance"];
				}
			}
		}
		std::cout << "Commands Step By Step : " << commands << std::endl;
	}
	std::cout << "Commands : " << commands << std::endl;
	return commands;
}

int FPathFindingA::getNextAngle(VectorPos2D posStart, VectorPos2D posEnd)
{
	VectorPos2D directionVector = { posEnd[0] - posStart[0], posEnd[1] - posStart[1] };
	FString direction;
	int nextAngle = 0;
	if (posEnd[0] > posStart[0]) {
		nextAngle = 180;
	}
	else {
		nextAngle = (int)((atan((posEnd[1] - posStart[1]) / (posEnd[0] - posStart[0]))) * (180 / PI));
	}
	

	std::cout << "angle : " << nextAngle << std::endl;
	return nextAngle;
}

bool FPathFindingA::isRigthDirection() const
{
	//Compare y Axis
	if (posStart[1] < posEnd[1]) {
		return true;
	}
	return false;
}

TMap<FString, VectorPos2D> FPathFindingA::validPositiontoEvaluate(VectorPos2D posToEvaluate, FString previousDirection)
{
	TMap<FString, VectorPos2D> posValid = posCheckPosition;

	if (!previousDirection.empty()) {
		if (previousDirection == "Nort") {
			posValid.erase("South");
		}
		else if (previousDirection == "South") {
			posValid.erase("Nort");
		}
		else if (previousDirection == "West") {
			posValid.erase("East");
		}
		else if (previousDirection == "East") {
			posValid.erase("West");
		}
	}

	//Compare Row
	if (posToEvaluate[0] == 0) {
		posValid.erase("Nort");
	}else if (posToEvaluate[0] == (numberOfColumn - 1)) {
		posValid.erase("South");
	}

	if (posToEvaluate[1] == 0) {
		posValid.erase("West");
	}else if (posToEvaluate[1] == (numberofRow - 1)) {
		posValid.erase("East");
	}
	return posValid;
}

void FPathFindingA::resetMapNavigation()
{
	mapNavigation = snapshotMapNavigation;
}

void FPathFindingA::printKeyofMap(TMap <FString, VectorPos2D> map) const
{
	for (TMap <FString, VectorPos2D>::iterator iter = map.begin(); iter != map.end(); ++iter)
	{
		FString k = iter->first;
		std::cout << "Key : " << k << std::endl;
	}
}

