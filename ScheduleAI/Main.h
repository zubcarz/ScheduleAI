#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "FNavigationRobot.h"

using FText = std::string;
using int32 = int;

using FText = std::string;

void welcomeGame();

void playSolution();

FText getValidMap();

FText readText(FText);

bool askToRunSolutionAgain();