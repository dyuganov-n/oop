#pragma once

#include "Game.h"

#include <iostream>
#include <vector>

#define FIELD_SIZE (10)
using namespace std;

class Console {
private:
	void clear();

public:	
	Console(){}

	void drawField(Game* game);
	void showStepsN(Game* game);
	void baseMessage();
	void gameOver() { cout << "Game Over!"; }

	string getCommand();
	string getArguements();
	size_t getNumArguement();

};
