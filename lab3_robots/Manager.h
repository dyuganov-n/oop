#pragma once

#include <vector>
#include <string>

#include "Sapper.h"
#include "Explorer.h"
#include "Mode.h"
#include "Parser.h"
#include "Environment.h"

#include <iostream>
#include <fstream>
using std::cin;


/// <summary>
/// Control interaction between sapper and explorer
/// </summary>
class Manager {
private:
	vector<pair<IMode*, IRobot*>> robots; // can Mode use their unique functions?

	Map robotsMap;
	Map globalMap;

	IMode* mode = nullptr; // Manager work 
	Parser* parser = nullptr;
	
	Environment* environment = nullptr; // global map is here
	Repeater* repeater = nullptr; // information exchange between robots 
	// data source 
	// delegate

	void changeMode(IMode* mode){}

	void step() {
		for (auto rbt : robots){
			this->updateGlobalMap();
			this->updateRobotsMap();
			//rbt.first->invokeCommand(rbt.second);
		}
	}
	// авто мод общий
	// нужен обработчик команд для робота и для самого менеджера 
	//void commandMandler();

	void updateGlobalMap() {
		for (const auto& item : repeater->getMapUpdates()) {
			globalMap.setCell(item.first, item.second);
			// this->environment->setObject(item.first, item.second);
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
		setGlobalMap(parser->getMapFileName());
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

	void setGlobalMap(const string& fileName) {
		size_t stringsCnt = 0;
		size_t symbolsInStrCnt = 0;
		char c;

		ifstream in(fileName);
		if (!in.is_open()) throw std::exception("Some problems with opening a file");

		// symbols cnt
		in >> c;
		while ((c != '\n') || (c != EOF)) {
			if (c != ' ') ++symbolsInStrCnt;
		}
		in.seekg(0, ios_base::beg); // in.seekg(0, std::ios::beg);

		// strings cnt
		in >> c;
		while (c != EOF) {
			if (c == '\n') ++stringsCnt;
		}
		in.seekg(0, ios_base::beg); // in.seekg(0, std::ios::beg);

		// creating map
		this->globalMap = Map(stringsCnt, symbolsInStrCnt);
		for (size_t i = 0; i < stringsCnt; ++i) {
			for (size_t j = 0; j < symbolsInStrCnt; ++j) {
				in >> c;
				if (c != ' ') globalMap.setCell({i, j}, (Object)c);
			}
		}
		in.close();
	}

	const Map* getMap() {
		return &(this->robotsMap);
	}

	void addRobot(IRobot* rb, IMode* md) {
		this->robots.push_back({ md, rb });
	}
	void createExplorer(IMode* md) {
		//Explorer* ex = new Explorer();
		//this->robots.push_back({ md, ex});
	}
};

