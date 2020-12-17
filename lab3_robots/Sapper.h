#pragma once

#include "Robot.h"

class Sapper : public IRobot {
private:
	const RobotClass _class = RobotClass::sapper;

public:
	Sapper(const Map& _map, const Coordinates& startPosition, Repeater* rep, Environment* env);
	Sapper() = delete;

	virtual ~Sapper() {
		this->internalMap.~Map();
		this->environment = nullptr;
		this->repeater = nullptr;
		
	}

	// getting information about robot
	const RobotClass& getRobotClass() const { return this->_class; }

	// unique actions
	void defuse();

};

