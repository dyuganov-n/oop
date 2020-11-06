#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Game.h"
#include "Console.h"

class Parser {
private:
	Game* game;

public:
	Parser(Game* _game);
	void getCommand(Console& console);
};

