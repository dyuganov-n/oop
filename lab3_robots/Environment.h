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
	Environment() = delete;
	~Environment() {
		delete globalMap;
		globalMap = nullptr;
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
	
private:
	Map* globalMap = nullptr;
	vector<Coordinates> collectedApples;
};

