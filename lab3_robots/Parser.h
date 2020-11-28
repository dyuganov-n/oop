#pragma once

#include "ConsoleInput.h"
#include "Command.h"
#include "optionparser/optionparser.h"

class Parser {
public:
	Parser(){
		input = nullptr;
	}
	Parser(ConsoleInput* _input) {
		input = _input;
	}
	~Parser(){}

	void getCommand() {
		try {
			string command = input->getCommand();
			if (command == "SET_MODE") {
				string arg = input->getCommand();
				if (arg == "manual") {

				}
				else if (arg == "auto") {

				}
				else if (arg == "scan") {
					size_t stepsN = input->getNumber();

				}
				else {
					throw exception("Wrong mode");
				}

			}
			else if (command == "MOVE") {
				string arg = input->getCommand();
				if (arg == "U") {

				}
				else if (arg == "R") {

				}
				else if (arg == "D") {

				}
				else if (arg == "L") {

				}
				else {
					throw exception("Wrong direction");
				}
			}
			else if (command == "SCAN") {

			}
			else if (command == "GRAB") {

			}
			else if (command == "SAPPER") {
				string sapperMode = input->getCommand();
				if (sapperMode == "ON") {

				}
				else if (sapperMode == "OFF") {

				}
				else {
					throw exception("Wrong sapper mode");
				}
			}
			else {
				throw exception("Wrong command");
			}
		}
		catch (const exception& e) {
			throw e;
		}
	}

	void setMapFileName() {
		// get file name from app args
	}
	void setConsoleInput(ConsoleInput* _input) {
		this->input = _input;
	}

	const string& getMapFileName() {
		return this->mapFileName;
	}

private:
	//ICommand* cmd = nullptr;

	string mapFileName;
	ConsoleInput* input = nullptr;
};

