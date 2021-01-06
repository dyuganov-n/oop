#pragma once

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
			if (dynamic_cast<ManualMode*>(mode)) {
				dynamic_cast<ManualMode*>(mode)->setAction(ManualModeAction::collect);
				mode->invokeCommand(robot);

				for (auto& item : manager->getRobots()) {
					if (item.second->getRobotClass() == RobotClass::sapper) {
						item.second->updateMap();
					}
				}
			}
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
				dynamic_cast<ManualMode*>(mode)->setAction(ManualModeAction::scan);
				dynamic_cast<ManualMode*>(mode)->invokeCommand(robot);

				for (auto& item : manager->getRobots()) {
					if (item.second->getRobotClass() == RobotClass::sapper) {
						item.second->updateMap();
					}
				}

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
			for (size_t i = 0; i < manager->getRobots().size(); ++i) {
				if (manager->getRobots().at(i).second->getRobotClass() == RobotClass::explorer) {
					IMode* mode = this->manager->getRobots().at(i).first;
					IRobot* robot = this->manager->getRobots().at(i).second;
					if (dynamic_cast<ManualMode*>(mode)) {
						dynamic_cast<ManualMode*>(mode)->setAction(ManualModeAction::move);
						dynamic_cast<ManualMode*>(mode)->setDirection(direction);
						mode->invokeCommand(robot);

						return;
					}
					else {
						throw exception("MoveManualCommand error. Explorer is not in manual mode.");
						return;
					}
				}
			}
			throw exception("No explorers in manager");
			return;
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
			if (dynamic_cast<ScanMode*>(mode)) {
				dynamic_cast<ScanMode*>(mode)->setStepsNumber(this->stepsNumber);
				mode->invokeCommand(robot);
			}
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
			if (dynamic_cast<AutoMode*>(mode)) {
				mode->invokeCommand(robot);
			}
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
	
	virtual void execute() override {
		//manager->getRobots()[0].first = newMode;
		manager->changeExplorerMode(newMode);
		if (dynamic_cast<ScanMode*>(newMode)) {
			Explorer* explorer = dynamic_cast<Explorer*>(manager->getRobots().at(0).second);
			if (explorer->getRobotClass() != RobotClass::explorer) {
				throw exception("ChangeModeCommand error. Can't invoke scan mode. Explorer is not explorer in manager.");
			}
			newMode->invokeCommand(explorer);
		}
		else if (dynamic_cast<AutoMode*>(newMode)) {
			AutoMode* md = dynamic_cast<AutoMode*>(newMode);
			if (manager->getRobots().size() == 2) {
				Explorer* explorer = dynamic_cast<Explorer*>(manager->getRobots().at(0).second);
				if (explorer->getRobotClass() != RobotClass::explorer) {
					throw exception("ChangeModeCommand error. Can't invoke auto mode. Explorer is not explorer in manager.");
				}
				Sapper* sapper = dynamic_cast<Sapper*>(manager->getRobots().at(1).second);
				if (sapper->getRobotClass() != RobotClass::sapper) {
					throw exception("ChangeModeCommand error. Can't invoke auto mode. Sapper is not sapper in manager.");
				}

				md->invokeCommand(explorer, sapper);
			}
			else {
				IRobot* explorer = dynamic_cast<Explorer*>(manager->getRobots().at(0).second);
				if (explorer->getRobotClass() != RobotClass::explorer) {
					throw exception("ChangeModeCommand error. Can't invoke scan mode. Explorer is not explorer in manager.");
				}
				newMode->invokeCommand(explorer);
			}
			
		}
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
			manager->createSapper();
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
			manager->deleteSapper();
		}
	}

private:
	Manager* manager = nullptr;
};

