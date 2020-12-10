#pragma once

#include "Direction.h"
#include "Mode.h"
#include "Manager.h"

//#include <string>
using namespace std;


class ICommand {
public:	
	virtual ~ICommand() = 0;
	virtual void execute() = 0;
};

// Manager
// Change mode of all robots work (manual, auto collect, auto scan)
class ChangeModeCommand : public ICommand {
public:
	ChangeModeCommand(Manager* manager, IMode* newMode) {
		this->newMode = newMode;
		this->manager = manager;
	}
	// interface
	virtual void execute() override {
		manager->getRobots()[0].first = newMode;
	}

private:
	IMode* newMode = nullptr;
	Manager* manager = nullptr;
};

// Explorer
// Commands for explorer in manaul mode (move, scan, collect)
class ManualModeCommand : public ICommand {
public:
	// interface
	virtual void execute() = 0;
};

class GrabManualCommand : public ManualModeCommand {
public:
	// interface
	virtual void execute() {
		
	}
};
class ScanManualCommand : public ManualModeCommand {
public:
	// interface
	virtual void execute() {
		// code
	}
};

class MoveManualCommand : public ManualModeCommand { 
public:
	MoveManualCommand(Manager* manager, const Direction& direction) {
		this->manager = manager;
		this->direction = direction;
	}
	virtual void execute() {
		IMode* mode = this->manager->getRobots().at(0).first;
		IRobot* robot = this->manager->getRobots().at(0).second;
		mode->invokeCommand(robot);
	}
private:
	Manager* manager = nullptr;
	Direction direction;
}; 

// Sapper
class SapperONCommand : public ICommand {
public:
	SapperONCommand(Manager* manager) {
		this->manager = manager;
	}
	~SapperONCommand() {
		this->manager = nullptr;
	}
	virtual void execute() {
		manager->CreateSapper();
	}
private:
	Manager* manager = nullptr;
};

class SapperOFFCommand : public ICommand {
public:
	virtual void execute() {

	}
};

