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
			repeater->NotifyCollect({ position.x, position.y });
		}
		else {
			throw exception("Explorer collect error. Global map has no apple at this position.");
		}
	}
}

void Explorer::_scan(const Coordinates& objCoords, vector<pair<Coordinates, Object>>& scanResult) {
	Object obj = this->environment->getObject(objCoords);
	scanResult.push_back({ objCoords, obj });
	this->internalMap.setObject(objCoords, obj);
}

void Explorer::scan() {
	vector<pair<Coordinates, Object>> scanResult;

	// left
	if (position.y != 0) {
		_scan({ position.x, position.y - 1 }, scanResult);
	}
	// right
	if (position.y != internalMap.getMapLength()) {
		_scan({ position.x, position.y + 1 }, scanResult);
	}
	//up
	if (position.x != 0) {
		_scan({ position.x - 1, position.y }, scanResult);
	}
	// down
	if (position.x != internalMap.getMapWidth()) {
		_scan({ position.x + 1, position.y }, scanResult);
	}
	//it's own cell
	_scan(position, scanResult);

	this->repeater->NotifyScan(scanResult);
}


