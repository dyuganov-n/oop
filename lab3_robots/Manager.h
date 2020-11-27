#pragma once

#include "Sapper.h"
#include "Explorer.h"
#include "Mode.h"
#include "Parser.h"

#include <vector>

// control interaction between sapper and explorer
class Manager {
private:
	vector<pair<IMode*, IRobot*>> robots; // can Mode use their unique functions?

	Map robotsMap;
	Map globalMap;

	IMode* mode; // Manager work 
	Parser* parser;
	Repeater repeater;
	// data source 
	// delegate

	void changeMode(IMode* mode){}

	void step() {
		for (auto rbt : robots){
			rbt.first->invokeCommand(rbt.second);
		}
		
	}
	// авто мод общий
	// нужен обработчик команд для робота и для самого менеджера 
	//void commandMandler();

public:	
	void handleCommand() {
		parser->getCommand();
	}
	
	const Object getObject(const Coordinates& coords) {
		return this->globalMap.getField()[coords.x][coords.y];
	}
	
	const vector<const IRobot*> getRobots() {
		vector<const IRobot*> result;
		for (auto r : robots) {
			result.push_back(r.second);
		}
		return result;
	}

	const Map* getMap() {
		return &(this->robotsMap);
	}
};

