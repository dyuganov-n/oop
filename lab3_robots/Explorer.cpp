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
	Coordinates coordLeft = { position.x, position.y - 1 };
	if (!environment->isOverGlobalMapEnd(coordLeft)) {
		if (coordLeft.x < 0) {
			Coordinates newPos = { position.x + static_cast<ptrdiff_t>(internalMap.getMapLength()), position.y };
			this->repeater->NotifyMove(position, newPos);
		}
		if (coordLeft.y < 0) {
			Coordinates newPos = { position.x, position.y + static_cast<ptrdiff_t>(internalMap.getMapWidth()) };
			this->repeater->NotifyMove(position, newPos);
		}
		_scan(coordLeft, scanResult);
	}
	// right
	Coordinates coordRight = { position.x, position.y + 1 };
	if (!environment->isOverGlobalMapEnd(coordRight)) {
		if (coordRight.x < 0) {
			Coordinates newPos = { position.x + static_cast<ptrdiff_t>(internalMap.getMapLength()), position.y };
			this->repeater->NotifyMove(position, newPos);
		}
		if (coordRight.y < 0) {
			Coordinates newPos = { position.x, position.y + static_cast<ptrdiff_t>(internalMap.getMapWidth()) };
			this->repeater->NotifyMove(position, newPos);
		}
		_scan(coordRight, scanResult);
	}
	//up
	Coordinates coordUp = { position.x - 1, position.y };
	if (!environment->isOverGlobalMapEnd(coordUp)) {
		if (coordUp.x < 0) {
			Coordinates newPos = { position.x + static_cast<ptrdiff_t>(internalMap.getMapLength()), position.y };
			this->repeater->NotifyMove(position, newPos);
		}
		if (coordUp.y < 0) {
			Coordinates newPos = {position.x, position.y + static_cast<ptrdiff_t>(internalMap.getMapWidth()) };
			this->repeater->NotifyMove(position, newPos);
		}
		_scan(coordUp, scanResult);
	}
	// down
	Coordinates coordDown = { position.x + 1, position.y };
	if (!environment->isOverGlobalMapEnd(coordDown)) {
		if (coordDown.x < 0) {
			Coordinates newPos = { position.x + static_cast<ptrdiff_t>(internalMap.getMapLength()), position.y };
			this->repeater->NotifyMove(position, { position.x + static_cast<ptrdiff_t>(internalMap.getMapLength()), position.y });
		}
		if (coordDown.y < 0) {
			Coordinates newPos = { position.x, position.y + static_cast<ptrdiff_t>(internalMap.getMapWidth()) };
			this->repeater->NotifyMove(position, newPos);
		}
		_scan(coordDown, scanResult);
	}
	//it's own cell
	_scan(position, scanResult);

	this->repeater->NotifyScan(scanResult);
}


