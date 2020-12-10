#pragma once

//#include "Parser.h" // Command, ConsoleInput inside
#include "Sapper.h" // IRobot, Repeater, Map, Environment, Direction inside
#include "Mode.h"
#include "Explorer.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using std::cin;


class Manager {
private:
	vector<pair<IMode*, IRobot*>> robots; // can Mode use their unique functions?

	//Parser* parser = nullptr;
	Environment* environment = nullptr; // global map is here
	Repeater* repeater = nullptr; // information exchange between robots 

public:	
	//Manager(Parser* prsr);
	Manager(const string& InputFileName);
	~Manager();

	//void setParser(Parser* newParser) { this->parser = newParser; }
	void setEnvironment(Environment* newEnvironment) { this->environment = newEnvironment; }
	Environment* getEnvironment() { return this->environment; }

	bool EnvironmentPtrIsNull() { return environment == nullptr ? true : false; }
	bool RepeaterPtrIsNull() { return repeater == nullptr ? true : false; }

	vector<pair<IMode*, IRobot*>>& getRobots() { return this->robots; }
	const Map& getRobotsMap() { return this->robots[0].second->getMap(); }

	Coordinates FindEmptySpace(const Map& map) const;

	void CreateExplorer();
	void CreateSapper();

	void ChangeExplorerMode(IMode* newMode);

	//void handleCommand(ICommand* command);
	//void Step();
};

