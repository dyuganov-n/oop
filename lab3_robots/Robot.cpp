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
	if (!(environment->isOverGlobalMapEnd(newPosition))) {
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
	updateMap();
	Coordinates newPosition = buildNewPosition(dir);
	if (isEmptyCell(newPosition)) { // able to step
		if (isAbleToStep(newPosition)) {
			if (newPosition.x < 0) { // offset, if map externed up or left
				//this->position.x += internalMap.getMapLength();
				newPosition.x += internalMap.getMapLength();
			}
			if (newPosition.y < 0) {
				//this->position.y += internalMap.getMapWidth();
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
	ptrdiff_t _x = 0, _y = 0;
	for (size_t i = 0; i < repeater->getMapUpdates().size(); ++i) {
		_x = repeater->getMapUpdates()[i].first.x;
		_y = repeater->getMapUpdates()[i].first.y;
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
