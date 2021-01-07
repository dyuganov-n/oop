#include "Robot.h"

bool IRobot::isAbleToStep(const Coordinates& coords) const {
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
	updateMap();

	Coordinates newPosition = buildNewPosition(dir);
	if (isEmptyCell(newPosition)) {
		if (isAbleToStep(newPosition)) {
			if (getRobotClass() == RobotClass::explorer && internalMap.getObject(newPosition) == Object::bomb) {
				return;
			}
			if (newPosition.x < 0) { // offset, if map externed up or left
				newPosition.x += internalMap.getMapLength();
			}
			if (newPosition.y < 0) {
				newPosition.y += internalMap.getMapWidth();
			}
			this->repeater->NotifyMove(getRobotClass(), position, newPosition);
			this->position = newPosition;
		}
		else {
			throw exception("Can't move to this cell.");
		}
	}
	else {
		//throw exception("Can't move. There is a robot in this cell");
	}
}

void IRobot::idling() {
	updateMap();
}

void IRobot::updateMap() {
	if (repeater->isAlone()) {
		return;
	}

	vector<vector<pair<Coordinates, Object>>> updates(repeater->getMapUpdates(getRobotClass()));
	Coordinates oldPosition(position);
	if (getRobotClass() == RobotClass::sapper) {
		this->position = repeater->getNewCoords(this->getRobotClass());
	}
	for (const auto item : updates) {
		internalMap.setObject(item);
	}
	repeater->NotifyMove(this->getRobotClass(), oldPosition, position);
}

void IRobot::move(const Coordinates& coords) {
	updateMap();
	if (coords.x < 0 || coords.x >= static_cast<ptrdiff_t>(getMap().getMapLength()) ||
		coords.y < 0 || coords.y >= static_cast<ptrdiff_t>(getMap().getMapWidth())) {
		throw exception("Robot coordinates move error. New coordinates are over robot map.");
	}
	else if (coords.x == position.x + 1 && coords.y == position.y) {
		this->move(Direction::down);
	}
	else if (coords.x == position.x - 1 && coords.y == position.y) {
		this->move(Direction::up);
	}
	else if (coords.x == position.x && coords.y == position.y + 1) {
		this->move(Direction::right);
	}
	else if (coords.x == position.x && coords.y == position.y - 1) {
		this->move(Direction::left);
	}
	else if (coords.x == position.x && coords.y == position.y) {
		return;
	}
	else {
		//throw exception("Robot coordinates move error. New coordinates are not in avaliable area.");
	}
}