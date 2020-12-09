#pragma once

#include "Robot.h"

#include <vector>
using std::vector;

class Explorer : public IRobot {
private:
	const RobotClass _class = RobotClass::explorer;
	Environment* environment = nullptr;

public:
	Explorer(const Coordinates& startPosition, Repeater* rep, Environment* env);
	Explorer(const Map& _map, const Coordinates& startPosition, Repeater* rep, Environment* env);
	Explorer() = delete;
	virtual ~Explorer();

	// getting information about robot
	const RobotClass& getRobotClass() const { return this->_class; }

	// other
	void setEnvironment(Environment* env) { this->environment = env; }

	// unique actions
	void collect();
	void scan();
};