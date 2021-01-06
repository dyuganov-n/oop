#pragma once

#include "Map.h"
#include "Environment.h"
#include "Repeater.h"
#include "Direction.h"
#include "RobotClass.h"

class IRobot {
public:
	virtual const RobotClass& getRobotClass() const = 0;

	// position
	virtual const Coordinates& getPosition() const { return this->position; }
	virtual void setCoordinates(const Coordinates& coords) { this->position = coords; }

	// map
	void setMap(Map& mp) { this->internalMap = mp; }
	const Map& getMap() { return this->internalMap; }

	// one cell step
	virtual void move(const Direction& dir);
	virtual void move(const Coordinates& coords);// move with check that new coords are in one step from robot

	virtual void idling();

	// unteraction with other robots and manager
	virtual void setRepeater(Repeater* rep) { this->repeater = rep; }
	virtual void updateMap();
	virtual Environment* getEnvironment() { return this->environment; }

protected:
	Map internalMap;
	Coordinates position = { 0, 0 };
	Repeater* repeater = nullptr;
	Environment* environment = nullptr;

private:
	bool isEmptyCell(const Coordinates& coords) const {
		return this->repeater->isEmptyCell(coords);
	}

	bool isAbleToStep(const Coordinates& coords);
	Coordinates buildNewPosition(const Direction& dir);	
	void setEnvironment(Environment* env) { this->environment = env; }
};