#include "Repeater.h"

bool Repeater::isEqual(const Coordinates& l, const Coordinates& r) const noexcept {
	if ((l.x == r.x) && (l.y == r.y)) {
		return true;
	}
	else {
		return false;
	}
}

void Repeater::NotifyRobotDeleted(const Coordinates& coords) {
	for (size_t i = 0; i < robotsPositions.size(); ++i) {
		if (isEqual(robotsPositions.at(i).first, coords)) {
			robotsPositions.erase(robotsPositions.begin() + i);
			return;
		}
	}
}

void Repeater::NotifyMove(const RobotClass& _class, const Coordinates& prevCoords, const Coordinates& newCoords) {
	if (!robotsPositions.empty()) {
		for (size_t i = 0; i < robotsPositions.size(); ++i) {
			if (isEqual(robotsPositions.at(i).first, prevCoords) && robotsPositions.at(i).second == _class) {
				robotsPositions.erase(robotsPositions.begin() + i);
				break;
			}
		}
		robotsPositions.push_back({ newCoords, _class });
	}
	else {
		throw exception("Notify move error. There are no robots positions in repeater.");
	}
}

void Repeater::NotifyMapExp(const ptrdiff_t& offsetX, const ptrdiff_t& offsetY) {
	for (auto& item : robotsPositions) {
		item.first.x += offsetX;
		item.first.y += offsetY;
	}
}

Coordinates Repeater::getSapperCoords() {
	const RobotClass _class = RobotClass::sapper;
	for (const auto& item : robotsPositions) {
		if (item.second == _class) {
			return item.first;
		}
	}
}

Coordinates Repeater::getNewCoords(const RobotClass& _class) {
	for (const auto& item : robotsPositions) {
		if (item.second == _class) {
			return item.first;
		}
	}
}

bool Repeater::isEmptyCell(const Coordinates& coords) const noexcept {
	for (const auto& i : robotsPositions) {
		if (isEqual(i.first, coords)) return false;
	}
	return true;
}

// get map updates for robot class robotClass
vector<vector<pair<Coordinates, Object>>> Repeater::getMapUpdates(const RobotClass& robotClass) {
	if (robotClass == RobotClass::explorer) {
		vector<vector<pair<Coordinates, Object>>> result(changesOfSapper);
		changesOfSapper.clear();
		return result;
	}
	else if (robotClass == RobotClass::sapper) {
		vector<vector<pair<Coordinates, Object>>> result(changesOfExplorer);
		changesOfExplorer.clear();
		return result;
	}
	else return {};
}


