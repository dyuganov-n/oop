#pragma once

#include "Robot.h"

#include <vector>
using std::vector;

class Explorer : public IRobot {
private:
	const RobotClass _class = RobotClass::explorer;

	Environment* environment = nullptr;
	//const RobotClass _class = RobotClass::explorer;
	//Map _map;
	//Coordinates pos = { 0, 0 };
	//Repeater* repeater = nullptr;
	//vector<Coordinates> resStorage; // coordinatees of collected apples + cnt

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
	Explorer(const Map& _map, const Coordinates& _coords, Repeater* rep, Environment* env) {
		this->_map = _map;
		this->pos = _coords;
		this->repeater = rep;
		this->environment = env;
	}

	~Explorer() {
		this->repeater = nullptr;
		this->environment = nullptr;
	}

	// getting information about robot
	const RobotClass& getRobotClass() const {
		return this->_class;
	}

	// other
	void setEnvironment(Environment* env) {
		this->environment = env;
	}

	// unique actions
	void collect() {
		if (_map.getField()[pos.x][pos.y] == Object::apple) {
			//this->resStorage.push_back({ pos.x, pos.y });
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