#pragma once

#include <iostream>
#include <string>

using namespace std;

#include "Game.h"
#include "Console.h"


class Parcer {
private:

	Game* game;

	string baseCommand; // first word 
	string commandValue; // second word (can be empty) 

	vector<size_t> getCoordinates(const string& in);
	size_t getNumberOfSteps(const string& in);

public:

	Parcer(Game* _game);
	void getCommand();
};

