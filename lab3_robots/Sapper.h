#pragma once

#include "Robot.h"
#include "Repeater.h"

class Sapper : public IRobot {
private:
	const RobotClass _class = RobotClass::sapper;
	Map _map;
	Coordinates pos = { 0, 0 };
	Repeater* repeater = nullptr;
	
	
public:
	Sapper() { 
		Coordinates coordinates = { 0, 0 };
		// init repeater
	}
	Sapper(const Map& _map) {
		this->_map = _map;
		Coordinates coordinates = { 0, 0 };
		// init repeater
	}
	Sapper(const Map& _map, const Coordinates& startPosition, Repeater* r) {
		this->_map = _map;
		pos = startPosition;
		// init repeater
	}
	virtual ~Sapper() {}
	
	// interface 
	const RobotClass& getRobotClass() const {
		return this->_class;
	}
	const Coordinates& getPosition() const  {
		return this->pos;
	}
	void setCoordinates(const Coordinates& coords) { 
		this->pos = coords; 
	}

	void updateMap() { // factory method
		
	}
	const Map& getMap() const  { 
		return this->_map; 
	}
	const Object** getField() const { this->getMap().getField(); }

	void move(const Direction& dir) {
		updateMap();
		
		// check cell is not out of map
		// cell is discovered && avaliable check 
		// move (change coords)
		// ask manager to check other robots 
	}

	// other
	void defuse() {
		if (_map.getField()[pos.x][pos.y] == Object::bomb) {
			_map.setCell({ pos.x, pos.y }, Object::empty);
			repeater->notifyDefuse({ pos.x, pos.y });
			this->_map.setCell(pos, Object::empty);
		}
	}

};

