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

vector<pair<Coordinates, Object>> Repeater::getMapUpdates() {
	vector<pair<Coordinates, Object>> res(changes);
	changes.clear();
	return res;
	//return this->changes;
}

void Repeater::DeleteElem(const size_t& idx) {
	if (idx >= this->changes.size() || idx < 0) {
		throw exception("Can't delete this element in changes vector");
	}
	this->changes.erase(changes.begin() + idx);
}
