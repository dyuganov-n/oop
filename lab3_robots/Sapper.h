#pragma once

#include "Robot.h"

class Sapper : public IRobot {
private:
	Map map;
	Coordinates coordinates = { 0, 0 };
	// Repeater repeater; // singleton  

public:
	Sapper() { 
		Coordinates coordinates = { 0, 0 }; 
	}
	Sapper(Map _map) {
		this->map = _map;
		Coordinates coordinates = { 0, 0 };
	}
	Sapper(Map _map, const Coordinates& coords) {
		this->map = _map;
		Coordinates coordinates = coords;
	}
	virtual ~Sapper() {}
	
	// interface 
	Coordinates getCoordinates() {
		return this->coordinates;
	}
	void setCoordinates(const Coordinates& coords) { 
		this->coordinates = coords; 
	}
	void updateMap(Map updatedMap) {
		this->map = updatedMap;
	}
	Map& getMap() { 
		return this->map; 
	}
	const object** getField() { this->getMap().getMap(); }

	void move(const Direction& dir) {
		// check cell is not out of map
		// cell is discovered && avaliable check 
		// move (change coords)
		// ask manager to check other robots 
	}

	void notify() {
		//repeater.notifyAll(); // sends its map version
	}

	// other
	void defuse() {
		if (map.getMap()[coordinates.x][coordinates.y] == object::bomb) {
			map.setCell(coordinates.x, coordinates.y, object::empty);
		}
	}

};

