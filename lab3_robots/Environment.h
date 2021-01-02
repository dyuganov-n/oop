#pragma once

#include "Map.h"
#include <vector>
using std::vector;

// Interaction with planet (using global map ptr)
class Environment {
public:
	Environment(const string& globalMapFileName);
	Environment();
	~Environment();

	void setGlobalMap(Map* newGlobalMap) { this->globalMap = newGlobalMap; }

	const Map& getGlobalMap() { return *(this->globalMap); }

	// global coords and robot coords are different!!!
	Object getObject(const Coordinates& coords) const  {
		return this->globalMap->getObject(coords);
	}
	Object getObjectForRobot(const Coordinates& coords) const {
		return this->globalMap->getObject(getGlobalCoords(coords));
	}

	void setObject(const Coordinates& coords, const Object& obj) {
		this->globalMap->setObject(coords, obj);
	}

	bool appleCollected(const Coordinates& coords);
	bool bombDefused(const Coordinates& coords);

	size_t getGlobalMapLength() const { return this->globalMap->getMapLength(); }
	size_t getGlobalMapWidth() const { return this->globalMap->getMapWidth(); }

	size_t getCollectedCnt() const { return this->collectedApples.size(); }

	Coordinates getGlobalCoords(const Coordinates& coords) const {
		return { robotsMapZeroCoord.x + coords.x, robotsMapZeroCoord.y + coords.y };
	}

	bool isOverGlobalMap(const Coordinates& coords) const; 

	void setRobotsMapZeroPoint(const Coordinates& coords) { 
		this->robotsMapZeroCoord = coords;
	}

	Coordinates getRobotsZeroPoint() const {
		return this->robotsMapZeroCoord;
	}

	vector<pair<Coordinates, Object>> scan(const vector<Coordinates>& coords);
	
private:
	Map* globalMap = nullptr;
	vector<Coordinates> collectedApples;
	Coordinates robotsMapZeroCoord = { 0, 0 }; // начало отсчета СК роботов в СК глобальной карты

};

