#include "Parcer.h"
//#include "Console.h"
//#include "Game.h"


#include <iostream>
using namespace std;

Parcer::Parcer(Game* _game) {
	this->game = _game;
}


vector<size_t> Parcer::getCoordinates(const string& in) {

	size_t x = in[0] - '0'; // char digit to int
	size_t y = in[1] - '0' - 17; // char letter to int
	vector<size_t> result = { x, y };

	return result;
}

size_t Parcer::getNumberOfSteps(const string& in) {
	return stoi(in);
}

void Parcer::getCommand() {

}