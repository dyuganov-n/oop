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
	vector<pair<IMode*, IRobot*>> robots;
	size_t robotsIdCnt = 0;

	Environment* environment = nullptr; // global map is here
	Repeater* repeater = nullptr; // information exchange between robots 

	bool noSappersCreated();
	bool explorerInManualMode();

public:	
	Manager(const string& InputFileName);
	~Manager();

	void setEnvironment(Environment* newEnvironment) { this->environment = newEnvironment; }
	Environment* getEnvironment() { return this->environment; }

	bool EnvironmentPtrIsNull() { return environment == nullptr ? true : false; }
	bool repeaterPtrIsNull() { return repeater == nullptr ? true : false; }

	vector<pair<IMode*, IRobot*>>& getRobots() { return this->robots; }
	const Map& getRobotsMap() { return this->robots[0].second->getMap(); }

	Coordinates findEmptySpace(const Map& map) const;

	void createExplorer();
	void createSapper();
	void deleteSapper();

	void changeExplorerMode(IMode* newMode);
};

