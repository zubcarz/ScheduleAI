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
#include <cmath> 


#define TMap std::map
#define PI 3.14159

using FString = std::string;
using int32 = int;
using VectorPos2D = std::array<double, 2>;
using ArrayList = std::vector<VectorPos2D>;
using Matriz = std::vector<std::vector<int>>;


class FPathFindingA
{
	public: 
		FPathFindingA();
		FPathFindingA(Matriz,int,int);
		FString moveTo(VectorPos2D, VectorPos2D, bool, bool);
		void printNavigationMap(VectorPos2D, VectorPos2D);
		void printArrayList(FString message, ArrayList list);
		bool isFinishMoves();
		void reset();

	private:
		int allowMoves;
		int gain;
		int currentMoves;
		int currentAngle;//Nort -> 180, Clockwise direction
		int numberofRow;
		int numberOfColumn;

		VectorPos2D posStart;
		VectorPos2D posEnd;
		Matriz mapNavigation;
		Matriz snapshotMapNavigation;

		TMap <FString, VectorPos2D> posCheckPosition;//List Character Valid
		TMap <FString, FString> movesValid;


		int getDistance(VectorPos2D) const;
		FString builderCommand(ArrayList,bool);
		int getNextAngle(VectorPos2D, VectorPos2D);
		bool isRigthDirection() const;
		void printKeyofMap(TMap <FString, VectorPos2D>) const;

		TMap <FString, VectorPos2D> validPositiontoEvaluate(VectorPos2D, FString);
		void resetMapNavigation();
};