#pragma once

#include "Map.h"
#include <vector>
using std::vector;

// Interaction with planet (using global map ptr)
class Environment {
public:
	Environment(const string &globalMapFileName) {
		if (!globalMapFileName.empty()) {
			//Map tmp(globalMapFileName);
			this->globalMap = new Map(globalMapFileName); 
		}
		else {
			throw exception("Global map name is not in parser");
		}
	}
	Environment() {
		this->globalMap = nullptr;
	}
	~Environment() {
		delete globalMap;
		globalMap = nullptr;
	}

	void setGlobalMap(Map* newGlobalMap) {
		this->globalMap = newGlobalMap;
	}

	const Map& getGlobalMap() { return *(this->globalMap); }

	// global coords and robot coords are different!!!
	const Object& getObject(const Coordinates& coords) const  {
		return this->globalMap->getObject(coords);
	}
	void setObject(const Coordinates& coords, const Object& obj) {
		this->globalMap->setObject(coords, obj);
	}

	bool appleCollected(const Coordinates& coords) {
		if (globalMap->getObject(coords) == Object::apple) {
			globalMap->setObject(coords, Object::empty);
			collectedApples.push_back(coords);
			return true;
		}
		else {
			return false;
		}
	}

	bool bombDefused(const Coordinates& coords) {
		if (globalMap->getObject(coords) == Object::bomb) {
			globalMap->setObject(coords, Object::empty);
			return true;
		}
		else {
			return false;
		}
	}

	size_t getGlobalMapLength() { return this->globalMap->getMapLength(); }
	size_t getGlobalMapWidth() { return this->globalMap->getMapWidth(); }

	size_t getCollectedCnt() { return this->collectedApples.size(); }

	Coordinates getGlobalCoords(const Coordinates& coords) {
		// координата + смещение относительно начала ск роботов
		return { robotsMapZeroCoord.x + coords.x, robotsMapZeroCoord.y + coords.y };
	}

	bool isOverGlobalMapEnd(const Coordinates& coords) {
		Coordinates globalRobPos = getGlobalCoords(coords);
		if (globalRobPos.x >= globalMap->getMapLength() || globalRobPos.x < 0 ||
			globalRobPos.y >= globalMap->getMapWidth() || globalRobPos.y < 0) {
			return true;
		}
		else {
			return false;
		}
	}

	void robotsMapExterned(const size_t& lenthOffset, const size_t& widthOffset ) {
		this->robotsMapZeroCoord.x -= lenthOffset;
		this->robotsMapZeroCoord.y -= widthOffset;
	}

	void setRobotsMapZeroPoint(const Coordinates& coords) {
		this->robotsMapZeroCoord = coords;
	}
	
private:
	Map* globalMap = nullptr;
	vector<Coordinates> collectedApples;
	Coordinates robotsMapZeroCoord = { 0, 0 }; // начало отсчета СК роботов в СК глобальной карты

};

