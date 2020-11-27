#pragma once

#include "Sapper.h"
#include "Explorer.h"
#include "Mode.h"
#include "Parser.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::cin;

// control interaction between sapper and explorer
class Manager {
private:
	vector<pair<IMode*, IRobot*>> robots; // can Mode use their unique functions?

	Map robotsMap;
	Map globalMap;

	IMode* mode = nullptr; // Manager work 
	Parser* parser = nullptr;
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

	Manager(Parser* prsr) {

	}
	~Manager() {
		
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

	void setGlobalMap(const string &fileName) {
		size_t stringsCnt = 0;
		size_t symbolsInStrCnt = 0;
		char c;

		ifstream in(fileName);
		if (!in.good()) throw std::exception("Some problems with opening a file");

		// symbols cnt
		in >> c;
		while (c != '/n' || c != EOF) {
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


};

