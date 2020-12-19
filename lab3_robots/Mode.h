#pragma once

#include "Robot.h"
#include "Explorer.h"
#include "Sapper.h"

// modes could be singletones

class IMode {
public:
	void virtual invokeCommand(IRobot* robot) = 0;
};

class IdlingMode : public IMode {
public:
	void invokeCommand(IRobot* robot) override;
	static IdlingMode* getInstance();

private:
	static IdlingMode* p_instance;
	IdlingMode() = default;
	~IdlingMode() { delete p_instance; }
};

enum class ManualModeAction { move, scan, collect, unknown };
class ManualMode : public IMode {
public:
	
	void invokeCommand(IRobot* robot) override;
	static ManualMode* getInstance();

	void setAction(const ManualModeAction &act){
		this->action = act;
	}
	void setDirection(const Direction& dir) {
		this->direction = dir;
	}

private:

	ManualModeAction action = ManualModeAction::unknown;
	Direction direction = Direction::unknown;

	static ManualMode* p_instance;
	ManualMode() = default;
	~ManualMode() {
		delete p_instance;
	}
};

class ScanMode : public IMode {
public:
	void invokeCommand(IRobot* robot) override;
	static ScanMode* getInstance();
	void setStepsNumber(size_t N) {
		this->stepsNumber = N;
	}
	
private:
	size_t stepsNumber = 0;
	vector<Coordinates> way;

	static ScanMode* p_instance;
	ScanMode() = default;
	~ScanMode() { delete p_instance; }
};

class AutoMode : public IMode {
public:
	void invokeCommand(IRobot* robot) override;
	static AutoMode* getInstance();

private:
	vector<Coordinates> sapperWay;
	vector<Coordinates> explorerWay;

	static AutoMode* p_instance;
	AutoMode() = default;
	~AutoMode() {
		delete p_instance;
	}
};


