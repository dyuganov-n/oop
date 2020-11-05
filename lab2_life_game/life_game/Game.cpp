#include "Game.h"


#include <iostream>
using namespace std;

Game::Game(){
	// arrays creations 
	// (don't want having problems with standart array[][] transfer)
	currField = new bool*[FIELD_SIZE];
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

void Game::makeStep() {
	++stepCnt;

	// copy cur to prev
	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			prevField[i][j] = currField[i][j];
		}
	}

	buildNewField();
}
void Game::buildNewField() {
	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			size_t neighborsCnt = 0;


		}
	}
}
