#include <iostream>

#include "Game.h"
#include "Console.h"
#include "Parser.h"

using namespace std;

int main() {

	Game game;
	Parser parser(&game);
	Console console;

	while (1) {
		parser.getCommand(console);
		console.drawField(&game);
	}


	return 0;
}