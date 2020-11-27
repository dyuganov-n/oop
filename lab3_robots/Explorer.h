#pragma once


// карту при необходимости запрашивает сам
// нужен еще класс окружения, из которого он подсасывает инфу о карте 
// (только не всю карту)

#include "Repeater.h"
#include "Robot.h"

#include <vector>
using std::vector;

class Explorer : public IRobot {
private:
	const RobotClass _class = RobotClass::explorer;

	Map map;
	Coordinates coords = { 0, 0 };

	vector<Coordinates> resStorage; // coordinatees of collected apples + cnt

	Repeater* repeater = nullptr;

public:
	Explorer() {
		this->repeater = nullptr;
	}
	Explorer(const Map& _map) {
		this->map = _map;
		this->repeater = nullptr;
	}
	Explorer(const Coordinates& _coords) {
		this->coords = _coords;
		this->repeater = nullptr;
	}
	Explorer(const Map& _map, const Coordinates& _coords) {
		this->coords = _coords;
		this->map = _map;
		this->repeater = nullptr;
	}
	Explorer(const Map& _map, const Coordinates& _coords, Repeater* rep) {
		this->map = _map;
		this->coords = _coords;
		this->repeater = rep;
	}
	~Explorer() {
		this->repeater = nullptr;
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
	void setMap(Map& mp) { this->map = mp; }
	void updateMap() {
		
	}

	const Object** getField() { this->getMap().getField(); }

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
		this->repeater->notifyScan({ {}, {}, {}, {} });
	}
};