#pragma once

#include "Direction.h"
#include "Mode.h"


#include <string>
using namespace std;

class ICommand {
public:	
	virtual void execute() = 0;
};

// Manager
/// <summary>
/// Change mode of all robots work (manual, auto collect, auto scan)
/// </summary>
class ChangeModeCommand : public ICommand {
public:
	ChangeModeCommand(vector<pair<IMode*, IRobot*>> robots) {	}
	// interface
	void execute() {}

	// other
	void setAutoScanSteps(const size_t& n) {
		this->autoScanSteps = n;
	}
	const size_t& getAutoScanSteps() {
		return this->autoScanSteps;
	}

private:
	string newMode;
	size_t autoScanSteps = 0;
};

// Explorer
/// <summary>
/// Commands for explorer in manaul mode (move, scan, collect)
/// </summary>
class ManualModeCommand : public ICommand {
public:
	// interface
	void execute() = 0;

protected:
	string command;
};

class GrabManualCommand : public ManualModeCommand {
public:
	// interface
	void execute() {
		// code
	}
};
class ScanManualCommand : public ManualModeCommand {
public:
	// interface
	void execute() {
		// code
	}
};

class MoveManualCommand : public ManualModeCommand { 
public:
	// interface
	void execute() {
		// code
	}

	// other
	void setDirection(const Direction& _dir) {
		this->direction = _dir;
	}
	const Direction& getDirection() {
		return this->direction;
	}
private:
	Direction direction;
}; 

// Sapper
class SapperConditionCommand : public ICommand {
public:
	void setCommand(const string& cmd) {
		newMode = cmd;
	}
	const string& getCommand() {
		return this->newMode;
	}
private:
	string newMode; // ON | OFF
};

