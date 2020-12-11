#pragma once

#include "Map.h"
#include "Environment.h"
#include "Repeater.h"
#include "Direction.h"

enum class RobotClass {
	explorer,
	sapper
};

class IRobot {
public:
	virtual const RobotClass& getRobotClass() const = 0;

	// position
	virtual const Coordinates& getCoordinates() const {
		return this->position;
	}
	virtual void setCoordinates(const Coordinates& coords) {
		this->position = coords;
	}

	// map
	void setMap(Map& mp) {
		this->internalMap = mp;
	}
	const Map& getMap() {
		return this->internalMap;
	}

	// main actions for all robots

	// no object check
	virtual void move(const Direction& dir) {
		updateMap();
		if (cellIsEmpty(buildNewPosition(dir))) {
			position = buildNewPosition(dir);
			this->repeater->NotifyMove(position, position); // add to position track if it is not there
		}
		else {
			throw exception("Can't move. There is a robot in this cell");
		}
	}

	void idling() {
		updateMap();
		this->repeater->NotifyMove(position, position); // add to position track if it is not there
	}

	// unteraction with other robots and manager
	virtual void setRepeater(Repeater* rep) {
		this->repeater = rep;
	}

protected:
	Map internalMap;
	Coordinates position = { 0, 0 };
	Repeater* repeater = nullptr;

	//Object** getField() { return internalMap.getField(); }
	
private:
	bool cellIsEmpty(const Coordinates& coords) const {
		return this->repeater->isEmptyCell(coords);
	}

	Coordinates buildNewPosition(const Direction& dir){
		try {
			Coordinates newPosition;
			switch (dir) {
			case Direction::down:
				if (position.x != internalMap.getMapLength()) { // or max val
					newPosition = { position.x + 1, position.y };
					if (internalMap.getObject(newPosition) != Object::unknown && 
						internalMap.getObject(newPosition) != Object::rock) {
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
					if (internalMap.getObject(newPosition) != Object::unknown &&
						internalMap.getObject(newPosition) != Object::rock) {
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
					if (internalMap.getObject(newPosition) != Object::unknown &&
						internalMap.getObject(newPosition) != Object::rock) {
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
					newPosition = { position.x, position.y + 1};
					if (internalMap.getObject(newPosition) != Object::unknown &&
						internalMap.getObject(newPosition) != Object::rock) {
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
		catch (const exception& e) {
			throw e;
		}
	}

	virtual void updateMap() {
		for (size_t i = 0; i < repeater->getMapUpdates().size(); ++i) {
			size_t _x = repeater->getMapUpdates()[i].first.x;
			size_t _y = repeater->getMapUpdates()[i].first.y;
			Object obj = repeater->getMapUpdates()[i].second;

			// cell is up to date check (all robots already have this cell in their maps)
			if (internalMap.getObject({_x, _y}) == obj) {
				repeater->deleteElem(i);
			}
			else {
				this->internalMap.setObject({ _x, _y }, obj);
			}
		}
	}
};