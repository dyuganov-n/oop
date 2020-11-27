#pragma once

#include "Robot.h"

// modes could be singletones

class IMode {
public:
	void virtual invokeCommand(IRobot* robot) = 0;
};


class ManualMode : public IMode {
public:
	void invokeCommand(IRobot* robot) {
		
	}
};

class ScanMode : public IMode {
public:
	void invokeCommand(IRobot* robot) {
		// 
	}
};

class AutoMode : public IMode {
public:
	void invokeCommand(IRobot* robot) {
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


