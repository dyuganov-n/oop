#pragma once

#include "Direction.h"
#include "Mode.h"
#include "Manager.h"

//#include <string>
using namespace std;

class ICommand {
public:	
	virtual void execute() = 0;
};

class IModeCommand : public ICommand {
	virtual void execute() = 0;
};

// Explorer
class ManualModeCommand : public IModeCommand {
public:
	// interface
	virtual void execute() = 0;
};

class GrabManualCommand : public ManualModeCommand {
public:
	GrabManualCommand(Manager* manager) {
		this->manager = manager;
	}
	virtual void execute() {
		if (manager == nullptr) {
			throw exception("MoveManualCommand execute error. Manager is nullptr.");
		}
		else {
			IMode* mode = this->manager->getRobots().at(0).first;
			IRobot* robot = this->manager->getRobots().at(0).second;
			if (dynamic_cast<ManualMode*>(mode)) mode->invokeCommand(robot);
			else {
				throw exception("GrabManualCommand error. Wrong robot mode for this command.");
			}
		}
	}
private:
	Manager* manager = nullptr;
};

class ScanManualCommand : public ManualModeCommand {
public:
	ScanManualCommand(Manager* manager) { this->manager = manager; }
	virtual void execute() {
		if (manager == nullptr) {
			throw exception("MoveManualCommand execute error. Manager is nullptr.");
		}
		else {
			IMode* mode = this->manager->getRobots().at(0).first;
			IRobot* robot = this->manager->getRobots().at(0).second;
			if (dynamic_cast<ManualMode*>(mode)) {
				dynamic_cast<ManualMode*>(mode)->invokeCommand(robot);
			}
			else {
				throw exception("ScanManualCommand error. Wrong robot mode for this command.");
			}
		}
	}
private:
	Manager* manager = nullptr;
};

class MoveManualCommand : public ManualModeCommand {
public:
	MoveManualCommand(Manager* manager, const Direction& direction) {
		this->manager = manager;
		this->direction = direction;
	}
	virtual void execute() {
		if (manager == nullptr) {
			throw exception("MoveManualCommand execute error. Manager is nullptr.");
		}
		else {
			IMode* mode = this->manager->getRobots().at(0).first;
			IRobot* robot = this->manager->getRobots().at(0).second;
			if (dynamic_cast<ManualMode*>(mode)) mode->invokeCommand(robot);
		}
	}
private:
	Manager* manager = nullptr;
	Direction direction;
};

class AutoScanCommand : public IModeCommand {
public:
	AutoScanCommand(Manager* manager, size_t N) {
		this->manager = manager;
		this->stepsNumber = N;
	}

	virtual void execute() {
		if (manager == nullptr) {
			throw exception("AutoScanCommand execute error. Manager is nullptr.");
		}
		else {
			IMode* mode = this->manager->getRobots().at(0).first;
			IRobot* robot = this->manager->getRobots().at(0).second;
			if (dynamic_cast<ScanMode*>(mode)) mode->invokeCommand(robot);
		}
	}

private:
	Manager* manager = nullptr;
	size_t stepsNumber = 0;
};

class AutoCollectCommand : public IModeCommand {
public:
	AutoCollectCommand(Manager* manager) {
		this->manager = manager;
	}

	virtual void execute() {
		if (manager == nullptr) {
			throw exception("AutoCollectCommand execute error. Manager is nullptr.");
		}
		else {
			IMode* mode = this->manager->getRobots().at(0).first;
			IRobot* robot = this->manager->getRobots().at(0).second;
			if (dynamic_cast<AutoMode*>(mode)) mode->invokeCommand(robot);
		}
	}

private:
	Manager* manager = nullptr;
};


// Manager
class IManagerCommand : public ICommand {
public:
	virtual void execute() = 0;
};

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

class SapperONCommand : public ICommand {
public:
	SapperONCommand(Manager* manager) { this->manager = manager; }
	~SapperONCommand() { this->manager = nullptr; }

	virtual void execute() { 
		if (manager == nullptr) {
			throw exception("SapperONCommand execute error. Manager is nullptr.");
		}
		else {
			manager->CreateSapper();
		}
	}

private:
	Manager* manager = nullptr;
};

class SapperOFFCommand : public ICommand {
public:
	SapperOFFCommand(Manager* manager) { this->manager = manager; }
	~SapperOFFCommand() { this->manager = nullptr; }

	virtual void execute() { 
		if (manager == nullptr) {
			throw exception("SapperOFFCommand execute error. Manager is nullptr.");
		}
		else {
			manager->DeleteSapper();
		}
	}

private:
	Manager* manager = nullptr;
};

