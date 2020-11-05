#pragma once

#include "Console.h"
//#include "Parcer.h"

#include <iostream>
using namespace std;

#define FIELD_SIZE (10)

class Game {
private:
	
	bool** currField;
	bool** prevField;
	size_t stepCnt;

	void makeStep();
	void buildNewField();

public:
	Game();
	Game(ifstream& field); // if the field was loaded from file

	~Game();
	
	void resetGame();

	bool** getCurField() {
		return currField;
	}



};

