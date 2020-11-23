#pragma once

#include "Sapper.h"
#include "Explorer.h"
#include "Mode.h"
#include "Parser.h"

#include <vector>


// control interaction between sapper and explorer
class Manager {
private:
	//vector<pair<IMode*, Explorer*>> explorers;
	//vector<pair<IMode*, Sapper*>> sappers;
	vector<pair<IMode*, IRobot*>> robots;
	Sapper* sapper;

	Map globalMap;

	IMode* mode; // Manager work 
	Parser* parser;
	Repeater* repeater;

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
	void handleCommand();
	Sapper* getSapper();
	Explorer* getExplorer();
};

