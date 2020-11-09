#include "Game.h"

using namespace std;

Game::Game() {
	// arrays creations 
	// (don't want having problems with standart array[][] transfer)
	currField = new bool* [FIELD_SIZE];
	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		currField[i] = new bool[FIELD_SIZE];
	}
	prevField = new bool* [FIELD_SIZE];
	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		prevField[i] = new bool[FIELD_SIZE];
	}

	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			this->currField[i][j] = 0;
			this->prevField[i][j] = 0;
		}
	}
	this->stepCnt = 0;
}

Game::~Game() {
	// memory free
	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		delete[] currField[i];
	}
	delete[] currField;
	currField = nullptr;

	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		delete[] prevField[i];
	}
	delete[] prevField;
	prevField = nullptr;
}

size_t Game::countNeighbors(const int& _x, const int& _y) const { // PROBLEMS HERE
	size_t cnt = 0;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {

			if (i == 0 && j == 0) continue; // cell itself

			if ((_x + i) < 0 && (_y + j) < 0) { // negative sides
				int x = 9;
				int y = 9;
				if (prevField[x][y]) ++cnt;
			}
			else if ((_y + j) < 0) {
				int x = (_x + i) % FIELD_SIZE;
				int y = 9;
				if (prevField[x][y]) ++cnt;
			}
			else if ((_x + i) < 0) {
				int x = 9;
				int y = (_y + j) % FIELD_SIZE;
				if (prevField[x][y]) ++cnt;
			}
			else { // normal case
				int x = (_x + i) % FIELD_SIZE;
				int y = (_y + j) % FIELD_SIZE;
				if (prevField[x][y]) ++cnt;
			}
		}
	}
	
	return cnt;
}

void Game::buildNewField() {
	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			size_t nbrsCnt = countNeighbors(i, j);
			if (prevField[i][j] == 0 && nbrsCnt == 3) currField[i][j] = 1;
			else if (prevField[i][j] == 1 && ((nbrsCnt < 2) || (nbrsCnt > 3))) currField[i][j] = 0;
		}
	}
}

void Game::nextStep() {
	try {
		++stepCnt;
		if (stepCnt == SIZE_MAX) throw exception("Too many steps");
		this->stopGame = true;

		// curField to prevField
		for (size_t i = 0; i < FIELD_SIZE; ++i) { 
			for (size_t j = 0; j < FIELD_SIZE; ++j) {
				prevField[i][j] = currField[i][j];
			}
		}
		buildNewField();

		// Game end check
		for (size_t i = 0; i < FIELD_SIZE; ++i) {
			for (size_t j = 0; j < FIELD_SIZE; ++j) {
				if (prevField[i][j] != currField[i][j]) {
					this->stopGame = false;
				}
			}
		}
		//if (this->stopGame) throw exception("Game finished!");
	}
	catch (const exception& e) {
		throw e;
	}
}

void Game::back(){
	try {
		if (cantGoBack) throw exception("Can't go back");
		--stepCnt;
		for (size_t i = 0; i < FIELD_SIZE; ++i) {
			for (size_t j = 0; j < FIELD_SIZE; ++j) {
				currField[i][j] = prevField[i][j];
				prevField[i][j] = 0;
			}
		}
	}
	catch (exception& e) {
		throw e;
	}
}

void Game::resetGame() {
	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			currField[i][j] = 0;
			prevField[i][j] = 0;
		}
	}
	stepCnt = 0;
}

void Game::loadField(const string& fileName) {
	try {
		ifstream field;
		if (!fileName.empty()) field.open(fileName.c_str()); // PROBLEM: can't open it 
		if (!field.is_open()) throw exception("File was not opened");
		if (!field.good()) throw exception("File problems");

		this->stepCnt = 0;
		
		for (size_t i = 0; i < FIELD_SIZE; ++i) {
			for (size_t j = 0; j < FIELD_SIZE; ++j) {
				field >> currField[i][j];
			}
		}
		field.close();
	}
	catch (exception& e) {
		throw e;
	}
}

void Game::saveField(const string& fileName) {
	try {
		//ofstream out("field.txt");
		ofstream outField;
		if (!fileName.empty()) outField.open(fileName.c_str()); // PROBLEM: can't open it 
		if (!outField.is_open()) throw exception("File was not opened");
		if (!outField.good()) throw exception("File problems");

		for (size_t i = 0; i < FIELD_SIZE; ++i) {
			for (size_t j = 0; j < FIELD_SIZE; ++j) {
				outField << currField[i][j] << ' ';
			}
			outField << endl;
		}
		outField.close();
	}
	catch (exception& e) {
		throw e;
	}
}

void Game::setCell(const size_t& x, const size_t& y) {
	try {
		if (x <= 9 && y <= 9) {
			currField[x][y] = 1;
		}
		else {
			throw exception("Wrong index");
		}
	}
	catch (exception& e) {
		throw e;
	}
}

void Game::clearCell(const size_t& x, const size_t& y) {
	try {
		if (x <= 9 && y <= 9) {
			currField[x][y] = 0;
		}
		else {
			throw exception("Wrong index");
		}
	}
	catch (exception& e) {
		throw e;
	}
}