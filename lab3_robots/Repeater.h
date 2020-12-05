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
		else {
			return false;
		}
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

	/// <summary>
	/// Delete prev position and add new to positions set.
	/// </summary>
	/// <param name="prevCoords"></param>
	/// <param name="newCoords"></param>
	void notifyMove(Coordinates& prevCoords, Coordinates& newCoords) {
		for (size_t i = 0; i < robotsPositions.size(); ++i) {
			if (isEqual(robotsPositions[i], prevCoords)) {
				robotsPositions.erase(robotsPositions.begin() + i);
			}
			robotsPositions.push_back(newCoords);
		}
	}

	/// <summary>
	/// Check that there is no other robot in this position
	/// </summary>
	/// <param name="coords"></param>
	/// <returns></returns>
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
		try {
			if (idx >= this->changes.size()) {
				throw exception("Can't delete this element in changes vector");
			}
			this->changes.erase(changes.begin() + idx);
		}
		catch (const exception& e) {
			throw e;
		}
	}
};
