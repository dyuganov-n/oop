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
		while (1) { 
			parser.getCommand(console);
			console.drawField(&game);
		}
	}
	catch (exception& e) {
		cout << "Opps... " << e.what() << endl;
		return 0;
	}


	return 0;
}