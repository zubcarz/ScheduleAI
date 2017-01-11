#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <array>

#include "FNavigationRobot.h"
#include "FPathFindingA.h"

using FText = std::string;
using int32 = int;
using FVectorPos2D = std::array<int, 2>;
using FArrayList = std::vector<FVectorPos2D>;
using FMatriz = std::vector<std::vector<int>>;

int32 main();

void welcomeGame();

void playSolution();

FText getValidMap();

FText readText(FText);

bool askToRunSolutionAgain();

void printInfoMap(ArrayList);

void printInfoNavigationMap(Matriz);

void outputFile(FString, int);

bool askToShowStepBystep();

FText ExePath();