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
	

	ICommand* parseCommand(Manager* mngr) {
		try {
			string command = input->getString();
			if (command == "SET_MODE") {
				string command = input->getString();
				if (command == "manual") {
					
				}
				else if (command == "auto") {

				}
				else if (command == "scan") {
					size_t stepsN = input->getNumber();

				}
				else {
					throw exception("Wrong mode");
				}

			}
			else if (command == "MOVE") {
				string dir = input->getString();
				if (dir == "U") {

				}
				else if (dir == "R") {

				}
				else if (dir == "D") {

				}
				else if (dir == "L") {

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
				string sapperMode = input->getString();
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
	string mapFileName;
	ConsoleInput* input = nullptr;
};

