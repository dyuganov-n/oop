#pragma once

#include "Robot.h"
#include "Map.h"

class Explorer : public IRobot {
private:
	Map map;
	Coordinates coordinates = { 0, 0 };
	// Repeater repeater; // singletone

public:
	Explorer() {
		this->coordinates = { 0, 0 };
	}
	Explorer(Map _map) {
		this->map = _map;
		this->coordinates = { 0, 0 };
	}
	Explorer(Map _map, const Coordinates& coords) {
		this->map = _map;
		this->coordinates = coords;
	}


	// interface 
	Coordinates getCoordinates() {
		return this->coordinates;
	}
	void setCoordinates(const Coordinates& coords) { this->coordinates = coords; }
	Map& getMap() { return this->map; }
	void updateMap(Map updatedMap) {
		this->map = updatedMap;
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
	void collect();
	void scan();

	//void setMode(const IMode& md); // scan or auto or manual
}
