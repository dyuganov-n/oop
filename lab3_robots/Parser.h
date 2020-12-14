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

	ICommand* parseCommand(Manager* mngr) {
		string command = input->getString();
		if (command == "set_mode") {
			string command = input->getString();
			if (command == "manual") {
				return new ChangeModeCommand(mngr, ManualMode::getInstance());
			}
			else if (command == "auto") {
				return new ChangeModeCommand(mngr, AutoMode::getInstance());
			}
			else if (command == "scan") {
				ScanMode* scanMode = ScanMode::getInstance();
				scanMode->setStepsNumber(input->getNumber());
				return new ChangeModeCommand(mngr, scanMode);
			}
			else {
				throw exception("Wrong mode");
			}

		}
		else if (command == "move") {
			string dir = input->getString();
			if (dir == "u") {
				return new MoveManualCommand(mngr, Direction::up);
			}
			else if (dir == "r") {
				return new MoveManualCommand(mngr, Direction::right);
			}
			else if (dir == "d") {
				return new MoveManualCommand(mngr, Direction::down);
			}
			else if (dir == "l") {
				return new MoveManualCommand(mngr, Direction::left);
			}
			else {
				throw exception("Wrong direction");
			}
		}
		else if (command == "scan") {
			return new ScanManualCommand(mngr);
		}
		else if (command == "grab") {
			return new GrabManualCommand(mngr);
		}
		else if (command == "sapper") {
			string sapperMode = input->getString();
			if (sapperMode == "on") {
				return new SapperONCommand(mngr);
			}
			else if (sapperMode == "off") {
				return new SapperOFFCommand(mngr);
			}
			else {
				throw exception("Wrong sapper mode");
			}
		}
		else {
			throw exception("Wrong command");
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
	string getMapFileName() {
		return this->mapFileName;
	}

private:
	string mapFileName;
	ConsoleInput* input = nullptr;

};

