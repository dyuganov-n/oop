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
	//vector<pair<Coordinates, Object>> changes;
	vector<vector<pair<Coordinates, Object>>> changesOfSapper;
	vector<vector<pair<Coordinates, Object>>> changesOfExplorer;

	vector<pair<Coordinates, RobotClass>> robotsPositions;

	bool isEqual(const Coordinates& l, const Coordinates& r) const noexcept;

public:
	Repeater() = default;
	~Repeater() = default;

	// makes this cell empty
	void NotifyDefuse(const Coordinates& coords) {
		//changes.push_back({ coords, Object::empty });
		changesOfSapper.push_back({ { coords, Object::empty } });
	}

	void NotifyScan(const vector<pair<Coordinates, Object>>& objects) noexcept {
		if (isAlone()) { // если робот один (explorer), то все изменения уже сделаны
			return;
		}
		//for (const auto& item : objects) {
		//	//this->changes.push_back(item);
		//}
		changesOfExplorer.push_back(objects);
	}

	// makes this cell empty
	void NotifyCollect(const Coordinates& coords) noexcept {
		if (isAlone()) { // если робот один (explorer), то все изменения уже сделаны
			return;
		}
		//changes.push_back({coords, Object::empty});
		changesOfExplorer.push_back({ { coords, Object::empty } });
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

	//vector<pair<Coordinates, Object>> getMapUpdates();
	//vector<pair<Coordinates, Object>> getMapUpdates(const RobotClass&);
	vector<vector<pair<Coordinates, Object>>> getMapUpdates(const RobotClass& robotClass);

	//void DeleteElem(const size_t& idx);

	bool isAlone() {
		return robotsPositions.size() == 1;
	}
};
