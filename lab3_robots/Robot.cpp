#include "Robot.h"

bool IRobot::isAbleToStep(const Coordinates& coords) {
	if (internalMap.getObject(coords) != Object::unknown &&
		internalMap.getObject(coords) != Object::rock) {
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
		if (position.x != internalMap.getMapLength()) { // or max val
			newPosition = { position.x + 1, position.y };
			if (isAbleToStep(newPosition)) { 
				return newPosition;
			}
			else {
				throw exception("Can't move. This area was not explored.");
			}
		}
		else {
			throw exception("Can't move. It is the end of explored map.");
		}
	case Direction::up:
		if (position.x != 0) { // or min val
			newPosition = { position.x - 1, position.y };
			if (isAbleToStep(newPosition)) {
				return newPosition;
			}
			else {
				throw exception("Can't move. This area was not explored.");
			}
		}
		else {
			throw exception("Can't move. It is the end of explored map.");
		}
	case Direction::left:
		if (position.y != 0) { // or min val
			newPosition = { position.x , position.y - 1 };
			if (isAbleToStep(newPosition)) {
				return newPosition;
			}
			else {
				throw exception("Can't move. This area was not explored.");
			}
		}
		else {
			throw exception("Can't move. It is the end of explored map.");
		}
	case Direction::right:
		if (position.y != internalMap.getMapLength()) {// or max val
			newPosition = { position.x, position.y + 1 };
			if (isAbleToStep(newPosition)) {
				return newPosition;
			}
			else {
				throw exception("Can't move. This area was not explored.");
			}
		}
		else {
			throw exception("Can't move. It is the end of explored map.");
		}
	default:
		throw exception("Wrong direction while trying to move");
	}
}

void IRobot::move(const Direction& dir) {
	updateMap();
	Coordinates newPosition = buildNewPosition(dir);
	if (isEmptyCell(newPosition)) {
		this->repeater->NotifyMove(position, newPosition); // add to position track if it is not there
		this->position = newPosition;
	}
	else {
		throw exception("Can't move. There is a robot in this cell");
	}
}

void IRobot::idling() {
	updateMap();
}

void IRobot::updateMap() {
	for (size_t i = 0; i < repeater->getMapUpdates().size(); ++i) {
		ptrdiff_t _x = repeater->getMapUpdates()[i].first.x;
		ptrdiff_t _y = repeater->getMapUpdates()[i].first.y;
		Object obj = repeater->getMapUpdates()[i].second;

		// cell is up to date check (all robots already have this cell in their maps)
		if (internalMap.getObject({ _x, _y }) == obj) {
			repeater->DeleteElem(i);
		}
		else {
			this->internalMap.setObject({ _x, _y }, obj);
		}
	}
}
