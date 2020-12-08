#pragma once

#include "Robot.h"

class Sapper : public IRobot {
private:
	const RobotClass _class = RobotClass::sapper;
	Environment* environment = nullptr;

public:
	Sapper(const Map& _map, const Coordinates& startPosition, Repeater* rep, Environment* env) {
		this->internalMap = _map;
		position = startPosition;
		this->environment = env;
		this->repeater = rep;
	}
	virtual ~Sapper() {}

	// getting information about robot
	const RobotClass& getRobotClass() const {
		return this->_class;
	}

	// unique actions
	void defuse() {
		if (internalMap.getObject(position) == Object::bomb) {
			internalMap.setCell(position, Object::empty);
			repeater->notifyDefuse(position);
			this->environment->bombDefused(position);
		}
	}

};

