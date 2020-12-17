#include "Explorer.h"

Explorer::Explorer(const Coordinates& startPosition, Repeater* rep, Environment* env) {
	this->position = startPosition;
	this->repeater = rep;
	this->environment = env;
	//this->id = _id;
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

void Explorer::scan() {
	const vector<Coordinates> coords = {
		{ position.x, position.y - 1 }, // left
		{ position.x, position.y + 1 }, // right
		{ position.x - 1, position.y }, // up
		{ position.x + 1, position.y }, // down
		position						// curr position
	};
	bool needScan = false;

	// no double scan check
	for (const auto& item : environment->scan(coords)) { 
		if (internalMap.getObject(item.first) != item.second) {
			needScan = true;
			break;
		}
	}
	if (!needScan) return;

	Coordinates newZeroPoint = environment->getRobotsZeroPoint();
	Coordinates oldPosition(position);
	for (auto& item : coords) {
		if (item.x < 0 || item.y < 0) {
			if (item.x < 0) {
				size_t offsetX = internalMap.getMapLength();
				position.x += offsetX;
				newZeroPoint.x -= offsetX;
			}
			if (item.y < 0) {
				size_t offsetY = internalMap.getMapWidth();
				position.y += offsetY;
				newZeroPoint.y -= offsetY;
			}
			repeater->NotifyMove(oldPosition, position);
			break;
		}
	}
	internalMap.setObject(environment->scan(coords));
	environment->setRobotsMapZeroPoint(newZeroPoint);
	repeater->NotifyScan(environment->scan(coords));
}
