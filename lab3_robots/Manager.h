#pragma once

#include "Parser.h" // Command, ConsoleInput inside
#include "Sapper.h" // IRobot, Repeater, Map, Environment, Direction inside
#include "Mode.h"
#include "Explorer.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using std::cin;


//Control interaction between sapper and explorer
class Manager {
private:
	vector<pair<IMode*, IRobot*>> robots; // can Mode use their unique functions?

	Parser* parser = nullptr;
	Environment* environment = nullptr; // global map is here
	Repeater* repeater = nullptr; // information exchange between robots 

	void changeMode(IMode* mode){}

public:	
	Manager(Parser* prsr);
	Manager();
	~Manager();

	void setParser(Parser* newParser) { this->parser = newParser; }
	void setEnvironment(Environment* newEnvironment) { this->environment = newEnvironment; }
	bool internalPtrsNonNull();

	Environment* getEnvironment() { return this->environment; }
	
	vector<IRobot*> getRobots();

	// for console view & creating new robots
	const Map& getRobotsMap() { return this->robots[0].second->getMap(); }

	Coordinates findEmptySpace(const Map& map) const;

	void createExplorer();

	void createSapper();

	void handleCommand(ICommand* command);

	void step();
};

