#pragma once

#include "Map.h"
#include <set>
#include <map>
#include <vector>
using std::pair;
using std::vector;
using std::set;



class Repeater {
private:
	vector<pair<Coordinates, Object>> changes;
	set<Coordinates> robotsPositions;
	
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
	void notifyMove(const Coordinates& prevCoords, const Coordinates& newCoords) {
		if (robotsPositions.count(prevCoords) > 0) {
			robotsPositions.erase(prevCoords);
		}
		robotsPositions.insert(newCoords);
	}

	/// <summary>
	/// Check that there is no other robot in this position
	/// </summary>
	/// <param name="coords"></param>
	/// <returns></returns>
	bool isEmptyCell(const Coordinates& coords) {
		if (robotsPositions.count(coords) != 0) return false;
		else return true;
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
