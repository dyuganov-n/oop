#include <iostream>

#include "Game.h"
#include "Console.h"
#include "Parser.h"
#include <fstream>

using namespace std;

int main() {

	try {
		Game game;
		Parser parser(&game);
		Console console;

		console.drawField(&game);
		while (!game.gameIsStopped()) { 
			parser.getCommand(console);
			console.drawField(&game);
		}
		console.gameOver();
	}
	catch (exception& e) {
		cout << "Oops... " << e.what() << endl;
		return 0;
	}

	return 0;
}