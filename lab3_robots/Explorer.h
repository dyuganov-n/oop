#pragma once

#include "Repeater.h"
#include "Robot.h"

#include <vector>
using std::vector;

class Explorer : public IRobot {
private:
	const RobotClass _class = RobotClass::explorer;

	Map map; // or Map ptr?
	Coordinates coords = { 0, 0 };

	vector<Coordinates> resStorage; // coordinatees of collected apples + cnt

	Repeater* repeater = nullptr;

public:
	Explorer() {
		this->coords = { 0, 0 };
		// init repeater
	}
	Explorer(Map _map) {
		this->map = _map;
		this->coords = { 0, 0 };
		// init repeater
	}
	Explorer(Map _map, const Coordinates& coords) {
		this->map = _map;
		this->coords = coords;
		// init repeater
	}

	// interface 
	const RobotClass& getRobotClass() const {
		return this->_class;
	}
	const Coordinates& getCoordinates() const {
		return this->coords;
	}
	void setCoordinates(const Coordinates& coords) { this->coords = coords; }
	const Map& getMap() const { return this->map; }
	void updateMap(Map updatedMap) {
		this->map = updatedMap;
	}

	const object** getField() { this->getMap().getField(); }

	void move(const Direction& dir) {
		// check cell is not out of map
		// cell is discovered && avaliable check 
		// move (change coords)
		// ask manager to check other robots 
	}

	// other
	void collect() {
		this->resStorage.push_back({ coords.x, coords.y });
		this->repeater->notifyCollect({ coords.x, coords.y });
	}

	void scan() {
		// scan
		this->repeater->notifyScan({ coords.x, coords.y }, { {}, {}, {}, {} });
	}
};