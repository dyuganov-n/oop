#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Game.h"
#include "Console.h"

class Parser {
private:

	Game* game;

	//string baseCommand; // first word 
	//sting commandValue; // second word (can be empty) 

	//vector<size_t> getCoordinates(const string& in);
	//size_t getNumberOfSteps(const string& in);

public:

	Parser(Game* _game);
	void getCommand(Console& console);
};

