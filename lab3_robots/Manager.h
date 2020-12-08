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
	Manager(Parser* prsr) {
		this->parser = prsr;
		this->environment = new Environment(prsr->getMapFileName());
		this->repeater = new Repeater;
	}
	Manager() {
		this->environment = nullptr;
		this->parser = nullptr;
		this->repeater = new Repeater;
	}
	~Manager() {
		delete environment;
		environment = nullptr;

		delete repeater;
		repeater = nullptr;

		parser = nullptr;
	}

	void setParser(Parser* newParser) { this->parser = newParser; }
	void setEnvironment(Environment* newEnvironment) { this->environment = newEnvironment; }
	bool internalPtrsNonNull() {
		if (parser == nullptr || environment == nullptr || repeater == nullptr) {
			return false;
		}
		return true;
	}

	Environment* getEnvironment() {
		return this->environment;
	}
	
	vector<IRobot*> getRobots() {
		vector<IRobot*> result;
		for (auto r : robots) {
			result.push_back(r.second);
		}
		return result;
	}

	// for console view & creating new robots
	const Map& getRobotsMap() { return this->robots[0].second->getMap(); }
	//Object** getRobotsField() { return this->robots[0].second->getMap()->getField(); }

	Coordinates findEmptySpace(const Map& map){
		if (repeater == nullptr) {
			throw exception("Can't find empty space. Repeater is nullptr.");
			return { 0, 0 };
		}
		Object obj;
		for (size_t i = 0; i < map.getMapLength(); ++i) {
			for (size_t j = 0; j < map.getMapWidth(); ++j) {
				obj = map.getObject({ i, j });
				if (obj == Object::empty || obj == Object::apple) {
					if (repeater->isEmptyCell({ i, j })) return { i, j };
				}
			}
		}
		throw exception("Can't find empty place for robot.");
		return { 0, 0 };
	}

	void createExplorer() {
		Coordinates newCoords = findEmptySpace(environment->getGlobalMap());
		IMode* newMode = new IdelingMode;
		Explorer* newExplorer = new Explorer(newCoords, repeater, environment);
		this->repeater->notifyMove(newCoords, newCoords);
		this->robots.push_back({newMode, newExplorer});
	}

	void createSapper() {
		if (robots.empty()) throw exception("Can't create sapper. There is no explorers.");
		Coordinates newCoords = findEmptySpace(robots[0].second->getMap());
		IMode* newMode = new IdelingMode;
		Sapper* newSapper = new Sapper(robots[0].second->getMap(), newCoords, repeater, environment);
		this->repeater->notifyMove(newCoords, newCoords);
		this->robots.push_back({ newMode, newSapper });
	}

	void handleCommand(ICommand* command) {
		command->execute();
		// sth else?
	}

	void step() {
		if (!internalPtrsNonNull()) throw exception("Manager can't make step. Some of internal pointers is nullptr.");
		for (auto rbt : robots) {
			//this->updateGlobalMap();
			ICommand* command = parser->parseCommand(robots);
			handleCommand(command);
			delete command;
		}
	}
};

