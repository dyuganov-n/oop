#pragma once

#include <exception>
using std::exception;

enum class Object : char {
	rock = 'r',
	bomb = 'b',
	empty = 'e',
	apple = 'a',
	unknown = 'u'
};
struct Coordinates {
	size_t x = 0;
	size_t y = 0;
};

class Map {
public:
	Map() {
		mapLength = minMapSize;
		mapWidth = minMapSize;

		field = new Object* [mapLength];
		for (size_t i = 0; i < mapLength; ++i) {
			field[i] = new Object[mapWidth];
		}
		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				this->field[i][j] = Object::unknown;
			}
		}
	}
	Map(const size_t& length, const size_t& width) {
		mapLength = length;
		mapWidth = width;

		field = new Object * [mapLength];
		for (size_t i = 0; i < mapLength; ++i) {
			field[i] = new Object[mapWidth];
		}
		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				this->field[i][j] = Object::unknown;
			}
		}
	}
	virtual ~Map() {
		for (size_t i = 0; i < this->getMapLength(); ++i) {
			delete[] field[i];
			field[i] = nullptr;
		}
		delete[] field;
		field = nullptr;
	}

	Object** getField() const { return this->field; } // const object** !!!

	const size_t& getMapLength() const { return this->mapLength; }
	const size_t& getMapWidth() const { return this->mapWidth; }

	void resourceFound() { ++resourcesOnMap; }
	void resourceCollected() { 
		if (resourcesOnMap) --resourcesOnMap;
		else throw exception("All resources of the map were collected");
	}
	const size_t& getResourcesOnMap() const { return this->resourcesOnMap; }

	void setCell(const Coordinates& coords, Object obj) {
		try {
			if (coords.x > this->mapLength || coords.y > this->mapWidth) {
				throw std::exception("Wrong index in SetCell");
			}
			this->field[coords.x][coords.y] = obj;
		}
		catch (const std::exception& e) { throw e; }
	}
	void fill(const Object &obj) {
		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				this->field[i][j] = obj;
			}
		}
	}
	void clear() {
		this->fill(Object::unknown);
	}

	Map operator=(const Map& other) {
		// cleaning mem
		for (size_t i = 0; i < minMapSize; ++i) {
			delete[] field[i];
			field[i] = nullptr;
		}
		delete[] field;
		field = nullptr;

		// copying
		this->mapLength = other.mapLength;
		this->mapWidth = other.mapWidth;

		field = new Object * [mapLength];
		for (size_t i = 0; i < mapLength; ++i) {
			field[i] = new Object[mapWidth];
		}
		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				this->field[i][j] = other.field[i][j];
			}
		}
		return *this;
	}

private:
	const size_t minMapSize = 1000;
	size_t mapLength = minMapSize;
	size_t mapWidth = minMapSize;

	Object** field = nullptr;

	size_t resourcesOnMap = 0; // don't need?
};

