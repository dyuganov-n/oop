#pragma once

#include "Repeater.h"
#include "Robot.h"

#include <vector>
using std::vector;

class Explorer : public IRobot {
private:
	const RobotClass _class = RobotClass::explorer;
	Map _map;
	Coordinates pos = { 0, 0 };
	Repeater* repeater = nullptr;
	Environment* environment = nullptr; // global map is here
	vector<Coordinates> resStorage; // coordinatees of collected apples + cnt

	const Object** getField() { this->getMap().getField(); }

public:
	Explorer() {
		this->repeater = nullptr;
	}
	Explorer(const Map& _map) {
		this->_map = _map;
		this->repeater = nullptr;
	}
	Explorer(const Coordinates& _coords) {
		this->pos = _coords;
		this->repeater = nullptr;
	}
	Explorer(const Map& _map, const Coordinates& _coords) {
		this->pos = _coords;
		this->_map = _map;
		this->repeater = nullptr;
	}
	Explorer(const Map& _map, const Coordinates& _coords, Repeater* rep) {
		this->_map = _map;
		this->pos = _coords;
		this->repeater = rep;
	}
	~Explorer() {
		this->repeater = nullptr;
	}

	// interface 
	const RobotClass& getRobotClass() const override {
		return this->_class;
	}

	const Coordinates& getCoordinates() const override {
		return this->pos;
	}
	void setCoordinates(const Coordinates& coords) override {
		this->pos = coords; 
	}
	const Map& getMap() const override { 
		return this->_map; 
	}
	void setMap(Map& mp) override {
		this->_map = mp;
	}
	void setEnvironment(Environment* env) {
		this->environment = env;
	}

	void updateMap() {
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
	void move(const Direction& dir) {
		// check cell is not out of map
		// cell is discovered && avaliable check 
		// move (change coords)
		// ask manager to check other robots 
	}
	

	// other
	void collect() {
		if (_map.getField()[pos.x][pos.y] == Object::apple) {
			this->resStorage.push_back({ pos.x, pos.y });
			this->repeater->notifyCollect({ pos.x, pos.y });
			this->_map.setCell(pos, Object::empty);
			//this->_map.resourceCollected();
		}
	}

	void scan() {
		vector<pair<Coordinates, Object>> scanResult;
		pair<Coordinates, Object> upObj;
		pair<Coordinates, Object> downObj;
		pair<Coordinates, Object> leftObj;
		pair<Coordinates, Object> rightObj;

		// up
		if (pos.y != 0) {
			Coordinates objCoords = { pos.x, pos.y - 1 };
			Object obj = this->environment->getObject(objCoords);
			scanResult.push_back({objCoords, obj});
			this->_map.setCell(objCoords, obj);
		}
		// down
		if (pos.y != _map.getMapLength()) {
			Coordinates objCoords = { pos.x, pos.y + 1 };
			Object obj = this->environment->getObject(objCoords);
			scanResult.push_back({ objCoords, obj });
			this->_map.setCell(objCoords, obj);
		}
		//left
		if (pos.x != 0) {
			Coordinates objCoords = { pos.x - 1, pos.y };
			Object obj = this->environment->getObject(objCoords);
			scanResult.push_back({ objCoords, obj });
			this->_map.setCell(objCoords, obj);
		}
		// right
		if (pos.x != _map.getMapWidth()) {
			Coordinates objCoords = { pos.x + 1, pos.y };
			Object obj = this->environment->getObject(objCoords);
			scanResult.push_back({ objCoords, obj });
			this->_map.setCell(objCoords, obj);
		}

		this->repeater->notifyScan(scanResult);
	}
};