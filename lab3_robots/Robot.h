#pragma once

#include "Map.h"
#include "Environment.h"
#include "Repeater.h"
#include "Direction.h"

enum class RobotClass {
	explorer,
	sapper
};

class IRobot {
public:
	virtual const RobotClass& getRobotClass() const = 0;

	// position
	virtual const Coordinates& getCoordinates() const { return this->position; }
	virtual void setCoordinates(const Coordinates& coords) { this->position = coords; }

	// map
	void setMap(Map& mp) {
		this->internalMap = mp;
	}
	const Map& getMap() {
		return this->internalMap;
	}

	// main actions for all robots

	virtual void move(const Direction& dir);

	void idling();

	// unteraction with other robots and manager
	virtual void setRepeater(Repeater* rep) { this->repeater = rep; }
	virtual void updateMap();

protected:
	Map internalMap;
	Coordinates position = { 0, 0 };
	Repeater* repeater = nullptr;

private:
	bool isEmptyCell(const Coordinates& coords) const {
		return this->repeater->isEmptyCell(coords);
	}

	bool isAbleToStep(const Coordinates& coords);
	Coordinates buildNewPosition(const Direction& dir);	
};