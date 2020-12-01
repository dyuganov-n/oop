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
		return this->pos;
	}
	virtual void setCoordinates(const Coordinates& coords) {
		this->pos = coords;
	}

	// map
	void setMap(Map& mp) {
		this->_map = mp;
	}
	const Map& getMap() const {
		return this->_map;
	}

	// main actions for all robots

	// no object check
	virtual void move(const Direction& dir) {
		updateMap();
		if (cellIsEmpty(buildNewPosition(dir))) {
			pos = buildNewPosition(dir);
			this->repeater->notifyMove(pos, pos);
		}
		else {
			throw exception("Can't move. There is a robot in this cell");
		}
	}
	void idling() {
		updateMap();
		// 
	}

	// unteraction with other robots and manager
	virtual void setRepeater(Repeater* rep) {
		this->repeater = rep;
	}

protected:
	Map _map;
	Coordinates pos = { 0, 0 };
	Repeater* repeater = nullptr;

	const Object** getField() { this->getMap().getField(); }

private:

	bool cellIsEmpty(const Coordinates& coords) {
		return this->repeater->isEmptyCell(coords);
	}

	const Coordinates& buildNewPosition(const Direction& dir) {
		try {
			Coordinates newPosition;
			switch (dir) {
			case Direction::down:
				if (pos.y != _map.getMapLength()) { // or max val
					newPosition = { pos.x, pos.y + 1 };
					if (this->getField()[newPosition.x][newPosition.y] != Object::unknown) {
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
				if (pos.y != 0) { // or min val
					newPosition = { pos.x, pos.y - 1 };
					if (this->getField()[newPosition.x][newPosition.y] != Object::unknown) {
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
				if (pos.x != 0) { // or min val
					newPosition = { pos.x - 1, pos.y };
					if (this->getField()[newPosition.x][newPosition.y] != Object::unknown) {
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
				if (pos.x != _map.getMapLength()) {// or max val
					newPosition = { pos.x + 1, pos.y };
					if (this->getField()[newPosition.x][newPosition.y] != Object::unknown) {
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
			if (getField()[_x][_y] == obj) {
				repeater->deleteElem(i);
			}
			else {
				this->_map.setCell({ _x, _y }, obj);
			}
		}
	}


};