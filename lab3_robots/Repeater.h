#pragma once

#include "Map.h"
#include "Environment.h"
#include "RobotClass.h"

#include <set>
#include <map>
#include <vector>
using std::pair;
using std::vector;

class Repeater {
private:
	vector<pair<Coordinates, Object>> changes;
	vector<pair<Coordinates, RobotClass>> robotsPositions;

	bool isEqual(const Coordinates& l, const Coordinates& r) const noexcept;

public:
	Repeater() = default;
	~Repeater() = default;

	// makes this cell empty
	void NotifyDefuse(const Coordinates& coords) {
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
	void NotifyRobotCreated(const RobotClass& _class, const Coordinates& coords) noexcept {
		robotsPositions.push_back({ coords, _class });
	}

	// delete coords
	void NotifyRobotDeleted(const Coordinates& coords);

	// delete old coords, add new
	void NotifyMove(const RobotClass& _class, const Coordinates& prevCoords, const Coordinates& newCoords);

	void NotifyMapExp(const ptrdiff_t& offsetX, const ptrdiff_t& offsetY);

	Coordinates getSapperCoords();

	Coordinates getNewCoords(const RobotClass& _class);

	// Check that there is no other robot in this position
	bool isEmptyCell(const Coordinates& coords) const noexcept;

	vector<pair<Coordinates, Object>> getMapUpdates();

	void DeleteElem(const size_t& idx);

	bool isAlone() {
		return !robotsPositions.size();
	}
};
