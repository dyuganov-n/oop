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

	// one cell move
	virtual void move(const Direction& dir);
	virtual void move(const Coordinates& coords); // move with check that new coords are in closest cell from robot

	virtual void idling();

	// interaction with other robots and manager
	virtual void setRepeater(Repeater* rep) { this->repeater = rep; }
	virtual void updateMap();
	virtual Environment* getEnvironment() { return this->environment; }

protected:
	Map internalMap;
	Coordinates position = { 0, 0 };
	Repeater* repeater = nullptr;
	Environment* environment = nullptr;

private:
	// no othe robots in this cell check
	bool isEmptyCell(const Coordinates& coords) const {
		return this->repeater->isEmptyCell(coords);
	}

	bool isAbleToStep(const Coordinates& coords) const; // cell is not "unknown" or "rock" check
	Coordinates buildNewPosition(const Direction& dir);	// returns new coordinates based on current position and chosen direction
	void setEnvironment(Environment* env) { this->environment = env; }
};