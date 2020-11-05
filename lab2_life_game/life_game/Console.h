#pragma once

#include "Game.h"
//#include "Parcer.h"

#include <iostream>
#include <vector>

#define FIELD_SIZE (10)
using namespace std;

	class Console {
private: 
	Game* game;

public:
	
	Console(Game* _game) {
		game = _game;
	}
	
	
	void drawField(Game* game);
	string getCommand();
	string getArguements();

	void clear();
};



