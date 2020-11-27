#pragma once

#include "Map.h"

class Environment
{
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

	const Object getObject(const Coordinates& coords) {
		return this->globalMap->getField()[coords.x][coords.y];
	}
	
private:
	Map* globalMap;

};

