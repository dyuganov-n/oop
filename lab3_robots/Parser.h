#pragma once

#include "Command.h"
#include "optionparser/optionparser.h"

class Parser {
public:
	Parser(){}
	~Parser(){}
	void getCommand();
	void setMapFileName() {
		// get file name from app args
	}

	const string& getMapFileName() {
		return this->mapFileName;
	}

private:
	//ICommand* cmd = nullptr;

	string mapFileName;

};

