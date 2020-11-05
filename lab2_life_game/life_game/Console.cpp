#include "Console.h"

#include "Parcer.h"
#include "Game.h"

#include <iostream>

using namespace std;

void Console::drawField(Game* game) {
	const char symbolTrue = '*';
	const char symbolFalse = '.';

	for (size_t i = 0; i < FIELD_SIZE; ++i) {
		for (size_t j = 0; j < FIELD_SIZE; ++j) {
			if ((*game).getCurField()[i][j] == 1) {
				cout << symbolTrue << ' ';
			}
			else {
				cout << symbolFalse << ' ';
			}
		}
		cout << endl;
	}
	cout << endl;
}

void Console::clear() {
	//system("cls");
}

string Console::getCommand() {
	cout << endl << "Waiting for command: " << endl;
	string command;
	cin >> command;
	return command;
}

string Console::getArguements() {
	string result;
	cin >> result;
	return result;
}

