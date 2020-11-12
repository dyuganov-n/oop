#include <iostream>

#include "Game.h"
#include "Console.h"
#include "Parser.h"
#include <fstream>

using namespace std;

int main() {
	
	Console console;
	Game game;
	Parser parser(&game);

	try {
		console.drawField(&game);
		while (!game.gameIsStopped()) { 
			parser.getCommand(console);
			console.drawField(&game);
		}
		console.gameOver();
	}
	catch (exception& e) {
		console.printException(e);
		return 0;
	}

	return 0;
}