#pragma once

#include "Map.h"

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
		this->globalMap->setCell(coords, obj);
	}
	void appleCollected(const Coordinates& coords) {

	}

	void bombDefused(const Coordinates& coords) {

	}

	//size_t getMapLength() { return this->globalMap->getMapLength(); }
	//size_t getMapWidth() { return this->globalMap->getMapWidth(); }

	
private:
	Map* globalMap = nullptr;
};

