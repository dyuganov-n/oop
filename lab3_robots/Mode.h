#pragma once

#include "Robot.h"
#include "Explorer.h"
#include "Command.h"

// modes could be singletones

class IMode {
public:
	void virtual invokeCommand(IRobot* robot, ICommand* cmd) = 0; // or use command inside?
};


class ManualMode : public IMode {
public:
	void invokeCommand(Explorer* robot, ManualModeCommand* cmd) {
		
	}
};

class ScanMode : public IMode {
public:
	void invokeCommandinvokeCommand(Explorer* robot, ICommand* cmd) {
		// 
	}
};

class AutoMode : public IMode {
public:
	void invokeCommandinvokeCommand(Explorer* robot, ICommand* cmd) {
		// find closest item (bomb or apple) and move
	}
};

/*
class Ideling : public IMode{ // need it?
public:
	void invokeCommand(IRobot* robot) {
		// code
	}
};
*/


