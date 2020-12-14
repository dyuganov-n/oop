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

	bool isEqual(const Coordinates& l, const Coordinates& r) const noexcept {
		if ((l.x == r.x) && (l.y == r.y)) {
			return true;
		}
		else {
			return false;
		}
	}
	

public:
	Repeater() = default;
	~Repeater() = default;

	// makes this cell empty
	void NotifyDefuse(const Coordinates& coords) noexcept {
		changes.push_back({ coords, Object::empty });
	}

	void NotifyScan(const vector<pair<Coordinates, Object>>& objects) noexcept {
		for (const auto& item : objects) {
			this->changes.push_back(item);
		}
	}

	// makes this cell empty
	void NotifyCollect(const Coordinates& coords) noexcept {
		changes.push_back({coords, Object::empty});
	}

	// add new coords
	void NotifyCreated(const Coordinates& newCoords) noexcept {
		robotsPositions.push_back(newCoords);
	}

	// delete old coords, add new
	void NotifyMove(const Coordinates& prevCoords, const Coordinates& newCoords) {
		if (!robotsPositions.empty()) {
			for (size_t i = 0; i < robotsPositions.size(); ++i) {
				if (isEqual(robotsPositions.at(i), prevCoords)) {
					robotsPositions.erase(robotsPositions.begin() + i);
				}
				robotsPositions.push_back(newCoords);
			}
		}
		else {
			throw exception("Notify move error. There are no robots positions in repeater.");
		}
	}

	// Check that there is no other robot in this position
	bool isEmptyCell(const Coordinates& coords) const noexcept {
		for (const auto& i : robotsPositions) {
			if (isEqual(i, coords)) return false;
		}
		return true;
	}

	const vector<pair<Coordinates, Object>>& getMapUpdates() const noexcept {
		return this->changes;
	}

	void DeleteElem(const size_t& idx) {
		if (idx >= this->changes.size() || idx < 0) {
			throw exception("Can't delete this element in changes vector");
		}
		this->changes.erase(changes.begin() + idx);
	}
};
