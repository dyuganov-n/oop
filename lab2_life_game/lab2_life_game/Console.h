#pragma once

#include "Game.h"

#include <iostream>
#include <vector>

#define FIELD_SIZE (10)
using namespace std;

class Console {
private:
	//Game* game;

public:
	/*
	Console(Game* _game) {
		game = _game;
	}
	*/
	
	Console(){}

	void drawField(Game* game);
	void showStepsN();

	string getCommand();
	string getArguements();
	size_t getNumArguement();

	void clear();
};
