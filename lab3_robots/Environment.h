#pragma once

#include "Map.h"

/// <summary>
/// Interaction with planet (global map).
/// </summary>
class Environment {
public:
	Environment(Map* _globalMap) {
		if (_globalMap == nullptr) throw std::exception("Environment map ptr is empty");
		this->globalMap = _globalMap;
	}
	Environment() {
		this->globalMap = nullptr;
	}
	~Environment() {
		this->globalMap = nullptr;
	}

	// global coords and robot coords are different!!!
	const Object& getObject(const Coordinates& coords) const  {
		return this->globalMap->getField()[coords.x][coords.y];
	}
	void setObject(const Coordinates& coords, const Object& obj) {
		this->globalMap->setCell(coords, obj);
	}

	//size_t getMapLength() { return this->globalMap->getMapLength(); }
	//size_t getMapWidth() { return this->globalMap->getMapWidth(); }

	
private:
	Map* globalMap = nullptr;

};

