#pragma once

#include "Robot.h"
#include "Repeater.h"

class Sapper : public IRobot {
private:
	const RobotClass _class = RobotClass::sapper;

	Map map;// or Map ptr?
	Coordinates coordinates = { 0, 0 };

	Repeater* repeater = nullptr;
	
public:
	Sapper() { 
		Coordinates coordinates = { 0, 0 };
		// init repeater
	}
	Sapper(const Map& _map) {
		this->map = _map;
		Coordinates coordinates = { 0, 0 };
		// init repeater
	}
	Sapper(const Map& _map, const Coordinates& coords) {
		this->map = _map;
		Coordinates coordinates = coords;
		// init repeater
	}
	virtual ~Sapper() {}
	
	// interface 
	const RobotClass& getRobotClass() const {
		return this->_class;
	}
	const Coordinates& getCoordinates() const  {
		return this->coordinates;
	}
	void setCoordinates(const Coordinates& coords) { 
		this->coordinates = coords; 
	}
	void updateMap(Map updatedMap) {
		this->map = updatedMap;
	}
	const Map& getMap() const  { 
		return this->map; 
	}
	const object** getField() const { this->getMap().getField(); }

	void move(const Direction& dir) {
		// check cell is not out of map
		// cell is discovered && avaliable check 
		// move (change coords)
		// ask manager to check other robots 
	}

	// other
	void defuse() {
		if (map.getField()[coordinates.x][coordinates.y] == object::bomb) {
			map.setCell(coordinates.x, coordinates.y, object::empty);
			repeater->notifyDefuse({ coordinates.x, coordinates.y });
		}
	}

};

