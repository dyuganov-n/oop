#pragma once

#include "Command.h"
#include "optionparser/optionparser.h"

class Parser {
public:
	Parser(){}
	~Parser(){}
	void getCommand();
	const string& getFileName() {
		// get file name from app args
	}

private:
	//ICommand* cmd = nullptr;

};

