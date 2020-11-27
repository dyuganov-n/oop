#pragma once

#include "Map.h"

enum class Direction : int { // need out of class
	up = 1,
	down = -1,
	left = -1,
	right = 1
};
struct Coordinates { // need out of class
	size_t x = 0;
	size_t y = 0;
};
enum class RobotClass {
	explorer,
	sapper
};

class IRobot {
public:
	virtual const RobotClass& getRobotClass() const = 0;

	virtual const Coordinates& getCoordinates() = 0;
	void virtual setCoordinates(const Coordinates& coords) = 0;
	//void virtual updateMap(Map updatedMap) = 0;
	//virtual const Map& getMap() = 0; // use reciever for this?
	//virtual const object** getField() = 0;

	void virtual move(const Direction& dir) = 0;

	void virtual updateMap() = 0; // use factory method?
	void virtual notifyAll() = 0;
};