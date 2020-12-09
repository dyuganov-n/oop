#include "Explorer.h"

Explorer::Explorer(const Coordinates& startPosition, Repeater* rep, Environment* env) {
	this->position = startPosition;
	this->repeater = rep;
	this->environment = env;
}

Explorer::Explorer(const Map& _map, const Coordinates& startPosition, Repeater* rep, Environment* env) {
	this->position = startPosition;
	this->repeater = rep;
	this->environment = env;
	this->internalMap = _map;
}


Explorer::~Explorer() {
	this->repeater = nullptr;
	this->environment = nullptr;
}

void Explorer::collect() {
	if (internalMap.getObject(position) == Object::apple) {
		if (environment->appleCollected(position)) {
			internalMap.setObject(position, Object::empty);
			repeater->notifyCollect({ position.x, position.y });
		}
	}
	else {
		throw exception("Explorer can't collect this object.");
	}
}

void Explorer::scan() {
	vector<pair<Coordinates, Object>> scanResult;
	pair<Coordinates, Object> upObj;
	pair<Coordinates, Object> downObj;
	pair<Coordinates, Object> leftObj;
	pair<Coordinates, Object> rightObj;

	// up
	if (position.y != 0) {
		Coordinates objCoords = { position.x, position.y - 1 };
		Object obj = this->environment->getObject(objCoords);
		scanResult.push_back({ objCoords, obj });
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


