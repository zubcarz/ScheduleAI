#pragma once

#include <iostream>
#include <string>
#include "main.h"

using FText = std::string;
using int32 = int;

int32 main()
{
	do {
		WelcomeGame();
	} while (AskToRunSolutionAgain());

	return 0; //exit game
}


void WelcomeGame()
{
	std::cout << "Welcome to ScheduleAI.\n" << std::endl;
	return;
}

void PlaySolution()
{
}

FText GetValidMap()
{
	FText pathFlieMap = "";


	return FText();
}

bool AskToRunSolutionAgain()
{
	std::cout << " Do you want to Run Solution again? Y/N : ";
	FText response = "";
	getline(std::cin, response);
	return (response[0] == 'Y' || response[0] == 'y') ? true : false;
	return false;
}
