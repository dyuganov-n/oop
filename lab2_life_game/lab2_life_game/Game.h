#pragma once

#include <iostream>
using namespace std;

#define FIELD_SIZE (10)

class Game {
private:
	bool** currField;
	bool** prevField;
	size_t stepCnt;

	void buildNewField();

public:
	Game();
	~Game();

	void resetGame();
	bool** getCurField() const { return currField;} // to print 

	void loadField(const string& fileName); // if the field was loaded from file
	void saveField(const string& fileName);

	void clearCel(const size_t& x, const size_t& y) { currField[x][y] = 0; }
	void setCel(const size_t& x, const size_t& y) { currField[x][y] = 1; }

	void nextStep();
	//void back();

	size_t getStepCnt() { return this->stepCnt; }
};

