#pragma once

#include "Map.h"
#include "Mode.h"
#include "Command.h"

class Robot {
public:
	size_t virtual getCurrX() = 0;
	size_t virtual getCurrY() = 0;

	void virtual setCurrX(const size_t& x) = 0;
	void virtual setCurrY(const size_t& y) = 0;

	enum class Direction { up, down, left, right };
	void virtual move(const Direction& dir) = 0;

	void virtual updateWorld();
	//void virtual setMode(const Mode& md) = 0;

	virtual object** getMap() = 0;

};



