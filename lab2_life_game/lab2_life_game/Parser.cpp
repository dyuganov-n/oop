#include "Parser.h"

using namespace std;

Parser::Parser(Game* _game) {
	this->game = _game;
}

void Parser::getCommand(Console& console) {
	string baseCommand, commandValue;
	baseCommand = console.getCommand();

	if (baseCommand == "reset") {
		(*game).resetGame();
	}

	if (baseCommand == "set") {
		string command = console.getArguements();	
		size_t x = command[0] - '0' - 17; // char letter to int
		size_t y = command[1] - '0'; // char digit to int
		(*game).setCel(x, y);
	}

	if (baseCommand == "clear") {
		string command = console.getArguements();
		size_t x = command[0] - '0' - 17; // char letter to int
		size_t y = command[1] - '0'; // char digit to int
		(*game).clearCel(x, y);
	}

	if (baseCommand == "step") {
		size_t N = console.getNumArguement();
		for (size_t i = 0; i < N; ++i) {
			(*game).nextStep();
		}
	}

	if (baseCommand == "back") {
		//(*game).back();
	}

	if (baseCommand == "save") {
		commandValue = console.getArguements();
		(*game).saveField(commandValue);
	}

	if (baseCommand == "load") {
		try {
			commandValue = console.getArguements();
			(*game).loadField(commandValue);
		}
		catch (const int& e) {
			if (e == 2) {
				cout << "Can't open the file." << endl;
				exit(2); // change
			}
		}
	}

}