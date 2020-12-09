#pragma once

/// TODO:
/// dynamic externtion
/// int coordinates 

#include <exception>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#include "Coordinates.h"
#include "Object.h"


class Map {
private:
	Object** field = nullptr;

	const size_t minMapSize = 1000;

	// symbols cnt in column (x)
	size_t mapLength = 0;

	// symbols cnt in line (y)
	size_t mapWidth = 0;

	size_t resourcesOnMap = 0; // don't need?

public:
	Map();
	Map(const size_t& length, const size_t& width);
	Map(const string& fileName);

	virtual ~Map();

	Object getObject(const Coordinates& coords) const;

	size_t getMapLength() const { return this->mapLength; }
	size_t getMapWidth() const { return this->mapWidth; }

	//void resourceFound() { ++resourcesOnMap; }

	void resourceCollected() { 
		if (resourcesOnMap > 0) --resourcesOnMap;
		else throw exception("All resources of the map were collected");
	}

	const size_t& getResourcesOnMap() const { return this->resourcesOnMap; }

	void setObject(const Coordinates& coords, Object obj);

	void fill(const Object& obj);

	Map operator=(const Map& other);

};

