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

	Coordinates offsetForSync = { 0, 0 }; // x, y

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
	void NotifyRobotDeleted(const Coordinates& coords) {
		for (size_t i = 0; i < robotsPositions.size(); ++i) {
			if (isEqual(robotsPositions.at(i).first, coords)) {
				robotsPositions.erase(robotsPositions.begin() + i);
				return;
			}
		}
	}

	// delete old coords, add new
	void NotifyMove(const RobotClass& _class, const Coordinates& prevCoords, const Coordinates& newCoords) {
		if (!robotsPositions.empty()) {
			for (size_t i = 0; i < robotsPositions.size(); ++i) {
				if (isEqual(robotsPositions.at(i).first, prevCoords) && robotsPositions.at(i).second == _class) {
					robotsPositions.erase(robotsPositions.begin() + i);
					break;
				}
			}
			robotsPositions.push_back({ newCoords, _class});
		}
		else {
			throw exception("Notify move error. There are no robots positions in repeater.");
		}
	}

	void NotifyMapExp(const ptrdiff_t& offsetX, const ptrdiff_t& offsetY) {
		for (auto& item : robotsPositions) {
			item.first.x += offsetX;
			item.first.y += offsetY;
		}
	}

	Coordinates getSapperCoords() {
		const RobotClass _class = RobotClass::sapper;
		for (const auto& item : robotsPositions) {
			if (item.second == _class) {
				return item.first;
			}
		}
	}

	Coordinates getNewCoords(const RobotClass& _class) {
		for (const auto& item : robotsPositions) {
			if (item.second == _class) {
				return item.first;
			}
		}
	}

	// Check that there is no other robot in this position
	bool isEmptyCell(const Coordinates& coords) const noexcept {
		for (const auto& i : robotsPositions) {
			if (isEqual(i.first, coords)) return false;
		}
		return true;
	}

	vector<pair<Coordinates, Object>> getMapUpdates() {
		vector<pair<Coordinates, Object>> res(changes);
		changes.clear();
		return res;
		//return this->changes;
	}

	void DeleteElem(const size_t& idx) {
		if (idx >= this->changes.size() || idx < 0) {
			throw exception("Can't delete this element in changes vector");
		}
		this->changes.erase(changes.begin() + idx);
	}

	bool isAlone() {
		return !robotsPositions.size();
	}
};
