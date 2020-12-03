#pragma once

#include "Parser.h" // Command, ConsoleInput inside
#include "Sapper.h" // IRobot, Repeater, Map, Environment, Direction inside
#include "Mode.h"
#include "Explorer.h"
//#include "Command.h"

#include <vector>
#include <string>
#include <memory> // for smart pointes
#include <iostream>
#include <fstream>
using std::cin;


/// <summary>
/// Control interaction between sapper and explorer
/// </summary>
class Manager {
private:
	vector<pair<IMode*, IRobot*>> robots; // can Mode use their unique functions?
	// add shared_ptr?

	Map robotsMap;
	Map globalMap;

	IMode* mode = nullptr; // Manager work 
	Parser* parser = nullptr;
	
	Environment* environment = nullptr; // global map is here
	Repeater* repeater = nullptr; // information exchange between robots 
	// data source 
	// delegate

	void changeMode(IMode* mode){}

	void updateGlobalMap() {
		for (const auto& item : repeater->getMapUpdates()) {
			//globalMap.setCell(item.first, item.second);
			this->environment->setObject(item.first, item.second);
		}
	}
	void updateRobotsMap() {
		for (const auto& item : repeater->getMapUpdates()) {
			robotsMap.setCell(item.first, item.second);
		}
	}

	

public:	
	Manager(Parser* prsr) {
		this->parser = prsr;
		globalMap = Map(parser->getMapFileName());
		this->repeater = new Repeater;
		this->environment = new Environment(&globalMap);
	}
	~Manager() {
		delete environment;
		environment = nullptr;

		delete repeater;
		repeater = nullptr;

		parser = nullptr;
		mode = nullptr;
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

	// for console view & creating new robots
	const Map* getRobotsMap() { return &(this->robotsMap); }
	const Object** getRobotsField() { return this->robotsMap.getField(); }

	Coordinates findEmptySpace() {
		for (int i = 0; i < globalMap.getMapLength(); ++i) {
			for (int j = 0; j < globalMap.getMapWidth(); ++j) {
				
			}
		}
	}

	void createExplorer(IMode* md) {
		
		// find good coords + explore this sell tp stand in it
		//Explorer* ex = new Explorer();
		//this->robots.push_back({ md, ex});
	}

	void createSapper() {
		Sapper* sp = new Sapper(this->robotsMap);
		// find good coords + explore this sell tp stand in it

	}

	void handleCommand(shared_ptr<ICommand> command) {
		command->execute();
		// sth else?
	}

	void step() {
		for (auto rbt : robots) {
			this->updateGlobalMap();
			this->updateRobotsMap();
			//rbt.first->invokeCommand(rbt.second);
			handleCommand(parser->parseCommand(this));
		}
	}
};

