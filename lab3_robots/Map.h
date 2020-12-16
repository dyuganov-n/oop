#pragma once

#include <exception>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#include "Coordinates.h"
#include "Object.h"

// (0,0)----> y (mapWidth)
// |
// |
// V
// x (mapLength)


class Map {
private:
	Object** field = nullptr;

	const size_t minMapSize = 3;

	// symbols cnt in column (x)
	size_t mapLength = 0;

	// symbols cnt in line (y)
	size_t mapWidth = 0;

	size_t resourcesOnMap = 0; // don't need?
	
	void deleteCurrField();
	
	// use current internal width and length
	Object** createField(const size_t& length, const size_t& width);
	void fillNewField(Object** newField, const Object& obj, const size_t& length, const size_t& width);
	void copyOldFieldToNew(Object** newField, const size_t& offsetLength, const size_t& offsetWidth);

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

