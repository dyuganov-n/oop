#pragma once

#include "Map.h"
#include <set>
#include <map>
#include <vector>
using std::pair;
using std::vector;

class Repeater {
private:
	vector<pair<Coordinates, Object>> changes;
	vector<Coordinates> robotsPositions;

	bool isEqual(const Coordinates& l, const Coordinates& r) const{
		if (l.x == r.x) {
			if (l.y == r.y) {
				return true;
			}
		}
		return false;
	}
	
public:
	Repeater() {}
	~Repeater() {}

	void notifyDefuse(const Coordinates& coords) {
		changes.push_back({ coords, Object::empty });
	}
	void notifyScan(const vector<pair<Coordinates, Object>>& objects) {
		for (const auto& item : objects) {
			this->changes.push_back(item);
		}
	}
	void notifyCollect(const Coordinates& coords) {
		changes.push_back({coords, Object::empty});
	}

	// Delete prev position and add new to positions set.
	void notifyMove(Coordinates& prevCoords, Coordinates& newCoords) {
		for (size_t i = 0; i < robotsPositions.size(); ++i) {
			if (isEqual(robotsPositions[i], prevCoords)) {
				robotsPositions.erase(robotsPositions.begin() + i);
			}
			robotsPositions.push_back(newCoords);
		}
	}


	// Check that there is no other robot in this position
	bool isEmptyCell(const Coordinates& coords) {
		for (const auto& i : robotsPositions) {
			if (isEqual(i, coords)) return false;
		}
		return true;
	}

	const vector<pair<Coordinates, Object>>& getMapUpdates() {
		return this->changes;
	}
	void deleteElem(const size_t& idx) {
		if (idx >= this->changes.size() || idx < 0) {
			throw exception("Can't delete this element in changes vector");
		}
		this->changes.erase(changes.begin() + idx);
	}
};
