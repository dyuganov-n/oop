#include "Robot.h"

// cell is not a bomb or rock check
bool IRobot::isAbleToStep(const Coordinates& coords) {
	Object tmp = internalMap.getObject(coords);
	if (tmp != Object::unknown && tmp != Object::rock) {
		return true;
	}
	else {
		return false;
	}
}

Coordinates IRobot::buildNewPosition(const Direction& dir) {
	Coordinates newPosition;
	switch (dir) {
	case Direction::down:
		newPosition = { position.x + 1, position.y };
		break;
	case Direction::up:
		newPosition = { position.x - 1, position.y };
		break;
	case Direction::left:
		newPosition = { position.x , position.y - 1 };
		break;
	case Direction::right:
		newPosition = { position.x, position.y + 1 };
		break;
	case Direction::unknown:
		throw exception("Robot buildNewPosition error. Unknown direction.");
		break;
	default: 
		throw exception("Wrong direction while trying to move");
		break;
	}
	if (!(environment->isOverGlobalMap(newPosition))) {
		if (isAbleToStep(newPosition)) {
			return newPosition;
		}
		else {
			throw exception("Can't move. This cell is not available.");
		}
	}
	else {
		throw exception("Can't move. It is the end of map.");
	}
}

void IRobot::move(const Direction& dir) {
	if(getRobotClass() != RobotClass::explorer) updateMap();

	Coordinates newPosition = buildNewPosition(dir);
	if (isEmptyCell(newPosition)) {
		if (isAbleToStep(newPosition)) {
			if (newPosition.x < 0) { // offset, if map externed up or left
				newPosition.x += internalMap.getMapLength();
			}
			if (newPosition.y < 0) {
				newPosition.y += internalMap.getMapWidth();
			}
			this->repeater->NotifyMove(position, newPosition);
			this->position = newPosition;
		}
		else {
			throw exception("Can't move to this cell.");
		}
	}
	else {
		throw exception("Can't move. There is a robot in this cell");
	}
}

void IRobot::idling() {
	updateMap();
}

void IRobot::updateMap() {
	if (repeater->isAlone()) { // если робот один (explorer), то все изменения уже сделаны
		return;
	}
	vector<pair<Coordinates, Object>> updates(repeater->getMapUpdates());
	Coordinates oldPosition(position);
	for (auto& item : updates) {
		if (item.first.x < 0 || item.first.y < 0) {
			if (item.first.x < 0) { //  сработает только после сканирования -> сапер поменяет свои координаты под расширяющуюся карту
				position.x += internalMap.getMapLength();
			}
			if (item.first.y < 0) {
				position.y += internalMap.getMapWidth();
			}
			repeater->NotifyMove(oldPosition, position);
			break;
		}
	}
	this->internalMap.setObject(updates);

	//ptrdiff_t _x = 0, _y = 0;
	//for (size_t i = 0; i < repeater->getMapUpdates().size(); ++i) {
	//	_x = repeater->getMapUpdates()[i].first.x;
	//	_y = repeater->getMapUpdates()[i].first.y;
	//	Object obj = repeater->getMapUpdates()[i].second;
	//	// cell is up to date check (all robots already have this cell in their maps)
	//	if (internalMap.getObject({ _x, _y }) == obj) {
	//		repeater->DeleteElem(i);
	//	}
	//	else {
	//		this->internalMap.setObject({ _x, _y }, obj);
	//	}
	//}
}
