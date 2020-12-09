#pragma once

#include "Robot.h"

#include <vector>
using std::vector;

class Explorer : public IRobot {
private:
	const RobotClass _class = RobotClass::explorer;
	Environment* environment = nullptr;

public:
	Explorer(const Coordinates& startPosition, Repeater* rep, Environment* env) {
		this->position = startPosition;
		this->repeater = rep;
		this->environment = env;
	}
	Explorer(const Map& _map, const Coordinates& startPosition, Repeater* rep, Environment* env) {
		this->position = startPosition;
		this->repeater = rep;
		this->environment = env;
		this->internalMap = _map;
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
		if (internalMap.getObject(position) == Object::apple) {
			if (environment->appleCollected(position)) {
				internalMap.setObject(position, Object::empty);
				repeater->notifyCollect({ position.x, position.y });
			}
			
		}
	}

	void scan() {
		vector<pair<Coordinates, Object>> scanResult;
		pair<Coordinates, Object> upObj;
		pair<Coordinates, Object> downObj;
		pair<Coordinates, Object> leftObj;
		pair<Coordinates, Object> rightObj;

		// up
		if (position.y != 0) {
			Coordinates objCoords = { position.x, position.y - 1 };
			Object obj = this->environment->getObject(objCoords);
			scanResult.push_back({objCoords, obj});
			this->internalMap.setObject(objCoords, obj);
		}
		// down
		if (position.y != internalMap.getMapLength()) {
			Coordinates objCoords = { position.x, position.y + 1 };
			Object obj = this->environment->getObject(objCoords);
			scanResult.push_back({ objCoords, obj });
			this->internalMap.setObject(objCoords, obj);
		}
		//left
		if (position.x != 0) {
			Coordinates objCoords = { position.x - 1, position.y };
			Object obj = this->environment->getObject(objCoords);
			scanResult.push_back({ objCoords, obj });
			this->internalMap.setObject(objCoords, obj);
		}
		// right
		if (position.x != internalMap.getMapWidth()) {
			Coordinates objCoords = { position.x + 1, position.y };
			Object obj = this->environment->getObject(objCoords);
			scanResult.push_back({ objCoords, obj });
			this->internalMap.setObject(objCoords, obj);
		}

		this->repeater->notifyScan(scanResult);
	}
};