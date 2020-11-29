#pragma once

#include "Map.h"
#include "Environment.h"
#include "Repeater.h"
#include "Direction.h"

enum class RobotClass {
	//unknown, 
	explorer,
	sapper
};

class IRobot {
public:
	// position
	virtual const Coordinates& getCoordinates() const {
		return this->pos;
	}
	virtual void setCoordinates(const Coordinates& coords) {
		this->pos = coords;
	}

	// map
	void setMap(Map& mp) {
		this->_map = mp;
	}
	const Map& getMap() const {
		return this->_map;
	}

	// main action for all robots
	virtual void move(const Direction& dir) {
		updateMap();
		// check cell is not out of map
		// cell is discovered && avaliable check 
		// move (change coords)
		// ask manager to check other robots 
	}
	void idling() {
		updateMap();
		// 
	}

	// unteraction with other robots and manager
	virtual void setRepeater(Repeater* rep) {
		this->repeater = rep;
	}
	virtual void updateMap() {
		for (size_t i = 0; i < repeater->getMapUpdates().size(); ++i) {
			size_t _x = repeater->getMapUpdates()[i].first.x;
			size_t _y = repeater->getMapUpdates()[i].first.y;
			Object obj = repeater->getMapUpdates()[i].second;

			// cell is up to date check (all robots already have this cell in their maps)
			if (getField()[_x][_y] == obj) {
				repeater->deleteElem(i);
			}
			else {
				this->_map.setCell({ _x, _y }, obj);
			}
		}
	}

protected:
	

	Map _map;
	Coordinates pos = { 0, 0 };
	Repeater* repeater = nullptr;

	const Object** getField() { this->getMap().getField(); }

private:
	
};