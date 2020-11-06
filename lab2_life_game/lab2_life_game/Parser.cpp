#include "Parser.h"

using namespace std;

Parser::Parser(Game* _game) {
	this->game = _game;
}

void Parser::getCommand(Console& console) {
	try {
		string baseCommand, commandValue;
		baseCommand = console.getCommand();

		if (baseCommand == "reset") {
			game->resetGame();
			game->setCantGoBack(true);
		}
		else if (baseCommand == "set") {
			string command = console.getArguements();
			size_t x = command[0] - '0' - 17; // char letter to int
			size_t y = command[1] - '0'; // char digit to int
			game->setCel(x, y);
		}
		else if (baseCommand == "clear") {
			string command = console.getArguements();
			size_t x = command[0] - '0' - 17; // char letter to int
			size_t y = command[1] - '0'; // char digit to int
			game->clearCel(x, y);
		}
		else if (baseCommand == "step") {
			game->setCantGoBack(false);
			size_t N = console.getNumArguement();
			for (size_t i = 0; i < N; ++i) {
				game->nextStep();
			}
		}
		else if (baseCommand == "back") {
			game->back();
			game->setCantGoBack(true);
		}
		else if (baseCommand == "save") {
			commandValue = console.getArguements();
			game->saveField(commandValue);
		}
		else if (baseCommand == "load") {
			game->setCantGoBack(true);
			commandValue = console.getArguements();
			game->loadField(commandValue);
		}
		else {
			throw exception("Wrong command");
		}
	}
	catch (exception& e) {
		throw e;
	}
}