#pragma once

#include "Robot.h"
#include "Explorer.h"

// modes could be singletones

class IMode {
public:
	void virtual invokeCommand(IRobot* robot) = 0;
};


class IdlingMode : public IMode {
public:
	void invokeCommand(IRobot* robot) {
		robot->idling();// sync map and coords
	}
};

class ManualMode : public IMode {
public:
	void invokeCommand(IRobot* robot) {
		
	}
	
};

class ScanMode : public IMode {
public:
	void invokeCommand(Explorer* robot) {
		
	}
};

class AutoMode : public IMode {
public:
	void invokeCommand(Explorer* robot) {
		// find closest item (bomb or apple) and move
	}
};


