#include "Game.h"

#include <iostream>
#include <fstream>
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

void Game::nextStep() {
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
		this->stepCnt = 0;
		ifstream field(fileName);
		if (!field.is_open()) throw 2; // file was not opened
		for (size_t i = 0; i < FIELD_SIZE; ++i) {
			for (size_t j = 0; j < FIELD_SIZE; ++j) {
				field >> currField[i][j];
			}
		}
		field.close();
	}
	catch (const int& e) {
		throw e;
	}
}

void Game::saveField(const string& fileName) {
	try {
		ofstream out(fileName);
		if (!out.is_open()) throw 2; // file was not opened
		for (size_t i = 0; i < FIELD_SIZE; ++i) {
			for (size_t j = 0; j < FIELD_SIZE; ++j) {
				out << currField[i][j];
			}
		}
		out.close();
	}
	catch (const int& e) {
		throw e;
	}
}
