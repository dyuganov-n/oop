#pragma once

#include "ConsoleInput.h"
#include "Command.h"
#include <vector>

using namespace std;
#include "optionparser/optionparser.h"

class Parser {
public:
	Parser(){
		input = nullptr;
	}
	Parser(ConsoleInput* _input) {
		input = _input;
	}
	~Parser() {
		delete input;
		input = nullptr;
	}

	ICommand* parseCommand(vector<pair<IMode*, IRobot*>>& robots) {
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

	// get file name from app args and store it inside parser
	void setMapFileName(int argc, char* argv[]) {
		argc -= (argc > 0); argv += (argc > 0); // skip program name argv[0] if present
		const option::Descriptor usage[] = { {0,0,nullptr,nullptr,nullptr,nullptr} };
		option::Stats  stats(usage, argc, argv);
		std::vector<option::Option> options(stats.options_max);
		std::vector<option::Option> buffer(stats.buffer_max);
		option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

		if (parse.error()) {
			throw exception("Error while parsing arguments");
		}

		if (parse.nonOptionsCount() != 1) {
			throw exception("Invalid amount of arguments");
		}

		this->mapFileName = parse.nonOption(0);
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

