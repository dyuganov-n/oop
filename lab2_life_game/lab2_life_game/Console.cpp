#include "Console.h"
#include "Game.h"

#include <iostream>

using namespace std;

void Console::drawField(Game* game) {
	this->clear();
	//this->baseMessage();

	const char symbolTrue = 'X';
	const char symbolFalse = '.';

	cout << "  "; 
	for (size_t i = 0; i < FIELD_SIZE; ++i) cout << i << ' ';
	cout << endl;

	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		cout << char('A' + i) << ' ';
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			if (game->getCurField()[i][j] == 1) {
				cout << symbolTrue << ' ';
			}
			else {
				cout << symbolFalse << ' ';
			}
		}
		cout << endl;
	}
	showStepsN(game);
}

void Console::showStepsN(Game* game) {
	cout << "Step: " << game->getStepCnt() << endl;
}

void Console::baseMessage(){
	cout << "_____Life_Game_____" << endl;
}

void Console::clear() {
	system("cls");
}

string Console::getCommand() {
	cout << "Waiting for command: " << endl;
	string command;
	cin >> command;
	return command;
}

string Console::getArguements() {
	string result;
	cin >> result;
	return result;
}

size_t Console::getNumArguement() {
	size_t result;
	cin >> result;
	return result;
}

void Console::printException(const exception& e) {
	cout << "Oops... " << e.what() << endl;
}
