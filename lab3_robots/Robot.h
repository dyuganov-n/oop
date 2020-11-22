#pragma once

#include "Map.h"
#include "Mode.h"
#include "Command.h"

enum class Direction : int {
	up = 1,
	down = -1,
	left = -1,
	right = 1
};
struct Coordinates {
	size_t x = 0;
	size_t y = 0;
};

class IRobot {
public:
	// map, coordinates
	virtual Coordinates getCoordinates() = 0;
	void virtual setCoordinates(const Coordinates& coords) = 0;
	void virtual updateMap(Map updatedMap) = 0;
	virtual Map& getMap() = 0; // use reciever for this?
	virtual const object** getField() = 0;

	// movement
	void virtual move(const Direction& dir) = 0;

	// notification system
	void virtual notify()
};



