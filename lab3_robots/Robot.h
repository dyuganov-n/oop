#pragma once

#include "Map.h"
#include "Environment.h"
#include "Repeater.h"
#include "Direction.h"

enum class RobotClass {
	explorer,
	sapper, 
	unknown
};

class IRobot {
public:
	// getting information about robot
	virtual const RobotClass& getRobotClass() const = 0;

	// position
	virtual const Coordinates& getCoordinates() const  = 0;
	virtual void setCoordinates(const Coordinates& coords) = 0;

	// map
	virtual void setMap(Map& mp) = 0;
	virtual const Map& getMap() const = 0;

	// main action for all robots
	virtual void move(const Direction& dir) = 0;

	// unteraction with other robots and manager
	virtual void setEnvironment(Environment* env) = 0;
	virtual void setRepeater(Repeater* rep) = 0;
	virtual void updateMap() = 0;

protected:
	/*
	const RobotClass _class = RobotClass::unknown;
	Map _map;
	Coordinates pos = { 0, 0 };
	Repeater* repeater = nullptr;
	*/
};