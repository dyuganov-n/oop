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
	// add shared_ptr?

	Map robotsMap;
	Map globalMap;

	//IMode* mode = nullptr; // Manager work 
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
		
		if (!prsr->getMapFileName().empty()) {
			globalMap = Map(parser->getMapFileName());
		}
		else throw exception("Global map name is not in parser");
		
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
	}
	
	const Object getObject(const Coordinates& coords) {
		return this->globalMap.getField()[coords.x][coords.y];
	}
	
	vector<IRobot*> getRobots() {
		vector<IRobot*> result;
		for (auto r : robots) {
			result.push_back(r.second);
		}
		return result;
	}

	// for console view & creating new robots
	const Map* getRobotsMap() { return &(this->robotsMap); }
	Object** getRobotsField() { return this->robotsMap.getField(); }

	Coordinates findEmptySpace(const Map* map) {
		Coordinates res = { 0, 0 };
		Object ob;
		for (size_t i = 0; i < map->getMapLength(); ++i) {
			for (size_t j = 0; j < map->getMapWidth(); ++j) {
				ob = map->getField()[i][j];
				if (ob == Object::empty || ob == Object::apple) {
					res.x = i;
					res.y = j;
					if(repeater->isEmptyCell(res)) return res;
				}
			}
		}
		throw exception("Can't find empty place for robot.");
		return res;
	}

	void createExplorer() {
		Coordinates newCoords = findEmptySpace(&globalMap);
		IMode* newMode = new IdelingMode;
		Explorer* newExplorer = new Explorer(robotsMap, newCoords, repeater, environment);
		this->repeater->notifyMove(newCoords, newCoords);
		this->robots.push_back({newMode, newExplorer});
	}

	void createSapper() {
		Coordinates newCoords = findEmptySpace(&robotsMap);
		IMode* newMode = new IdelingMode;
		Sapper* newSapper = new Sapper(robotsMap, newCoords, repeater);
		this->repeater->notifyMove(newCoords, newCoords);
		this->robots.push_back({ newMode, newSapper });
	}

	void handleCommand(ICommand* command) {
		command->execute();
		// sth else?
	}

	void step() {
		for (auto rbt : robots) {
			this->updateGlobalMap();
			this->updateRobotsMap();
			//rbt.first->invokeCommand(rbt.second);
			ICommand* command = parser->parseCommand(robots);
			handleCommand(command);
			delete command;
		}
	}
};

