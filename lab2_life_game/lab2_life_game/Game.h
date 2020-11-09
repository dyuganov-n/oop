#pragma once

#include <iostream>
#include <fstream>
using namespace std;

#define FIELD_SIZE (10)


class Game {
private:
	bool** currField;
	bool** prevField;

	size_t stepCnt = 0;
	bool cantGoBack = 1;

	bool stopGame = 0;

	void buildNewField();
	size_t countNeighbors(const int& x, const int& y) const;

public:
	Game();
	~Game();	

	void setCantGoBack(const bool& val) { cantGoBack = val; }
	bool gameIsStopped() { return stopGame; }

	void resetGame();
	bool** getCurField() const { return currField; } // for console to print 

	void loadField(const string& fileName); // if the field was loaded from file
	void saveField(const string& fileName);

	void clearCell(const size_t& x, const size_t& y); 
	void setCell(const size_t& x, const size_t& y); 

	void nextStep();
	void back();

	size_t getStepCnt() { return this->stepCnt; }
};

