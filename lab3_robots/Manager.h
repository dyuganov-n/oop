#pragma once

#include "Sapper.h"
#include "Explorer.h"
#include "Mode.h"
#include "Parser.h"

#include <vector>


// control interaction between sapper and explorer
class Manager {
private:
	vector<pair<IMode*, Explorer*>> explorers;
	Sapper* sapper;

	Map globalMap;

	IMode* mode;
	Parser* parser;

	void step() {
		mode.invokeCommand(cmd);
	}
	// авто мод общий
	// нужен обработчик команд для робота и для самого менеджера 
	//void commandMandler();

public:
	Manager(Explorer* ex, Sapper* sp) {
		this->explorer = ex;
		this->sapper = sp;
	}


	
	void handleCommand(); // void changeMode();


	void setExplorer(Explorer* ex) { this->explorer = ex; }
	void setSapper(Sapper* sp) { this->sapper = sp; }

};

