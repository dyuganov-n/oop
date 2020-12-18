#include "Environment.h"

Environment::Environment(const string& globalMapFileName) {
	if (!globalMapFileName.empty()) {
		//Map tmp(globalMapFileName);
		this->globalMap = new Map(globalMapFileName);
	}
	else {
		throw exception("Global map name is not in parser");
	}
}

Environment::Environment() {
	this->globalMap = nullptr;
}

Environment::~Environment() {
	delete globalMap;
	globalMap = nullptr;
}

bool Environment::appleCollected(const Coordinates& coords) {
	if (getObjectForRobot(coords) == Object::apple) {
		globalMap->setObject(getGlobalCoords(coords), Object::empty);
		collectedApples.push_back(coords);
		return true;
	}
	else {
		return false;
	}
}

bool Environment::bombDefused(const Coordinates& coords) {
	if (getObjectForRobot(coords) == Object::bomb) {
		globalMap->setObject(coords, Object::empty);
		return true;
	}
	else {
		return false;
	}
}

bool Environment::isOverGlobalMap(const Coordinates& coords) const {
	Coordinates globalRobPos = getGlobalCoords(coords);

	if (globalRobPos.x >= static_cast<ptrdiff_t>(globalMap->getMapLength()) || globalRobPos.x < 0 ||
		globalRobPos.y >= static_cast<ptrdiff_t>(globalMap->getMapWidth()) || globalRobPos.y < 0) {
		return true;
	}
	else {
		return false;
	}
}

vector<pair<Coordinates, Object>> Environment::scan(const vector<Coordinates>& coords) {
	vector<pair<Coordinates, Object>> result;
	for (const auto& item : coords) {
		if (!isOverGlobalMap(item)) {
			result.push_back({ item, getObjectForRobot(item) });
		}
	}
	return result;
}