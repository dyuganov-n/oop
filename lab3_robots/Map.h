#pragma once

#include <exception>
using std::exception;

enum class object : char {
	rock = 'r',
	bomb = 'b',
	empty = 'e',
	apple = 'a',
	unknown = 'u'
};

class Map {
public:
	Map() {
		mapLength = minMapSize;
		mapWidth = minMapSize;

		map = new object* [mapLength];
		for (size_t i = 0; i < mapLength; ++i) {
			map[i] = new object[mapWidth];
		}
		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				this->map[i][j] = object::unknown;
			}
		}
	}
	Map(const size_t& length, const size_t& width) {
		mapLength = length;
		mapWidth = width;

		map = new object * [mapLength];
		for (size_t i = 0; i < mapLength; ++i) {
			map[i] = new object[mapWidth];
		}
		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				this->map[i][j] = object::unknown;
			}
		}
	}
	virtual ~Map() {
		for (size_t i = 0; i < this->getMapLength(); ++i) {
			delete[] map[i];
			map[i] = nullptr;
		}
		delete[] map;
		map = nullptr;
	}

	object** getField() const { return this->map; } // const object** !!!

	const size_t& getMapLength() const { return this->mapLength; }
	const size_t& getMapWidth() const { return this->mapWidth; }

	void resourceFound() { ++resourcesOnMap; }
	void resourceCollected() { 
		if (resourcesOnMap) --resourcesOnMap;
		else throw exception("All resources of the map were collected");
	}
	const size_t& getResourcesOnMap() const { return this->resourcesOnMap; }

	void setCell(const size_t& x, const size_t& y, object obj) {
		try {
			if (x > this->mapLength || y > this->mapWidth) {
				throw std::exception("Wrong index in SetCell");
			}
			this->map[x][y] = obj;
		}
		catch (const std::exception& e) { throw e; }
	}
	void fill(const object &obj) {
		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				this->map[i][j] = obj;
			}
		}
	}
	void clear() {
		this->fill(object::unknown);
	}

	Map operator=(const Map& other) {
		// cleaning mem
		for (size_t i = 0; i < minMapSize; ++i) {
			delete[] map[i];
			map[i] = nullptr;
		}
		delete[] map;
		map = nullptr;

		// copying
		this->mapLength = other.mapLength;
		this->mapWidth = other.mapWidth;

		map = new object * [mapLength];
		for (size_t i = 0; i < mapLength; ++i) {
			map[i] = new object[mapWidth];
		}
		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				this->map[i][j] = other.map[i][j];
			}
		}
		return *this;
	}

private:
	const size_t minMapSize = 1000;
	size_t mapLength = minMapSize;
	size_t mapWidth = minMapSize;

	object** map = nullptr;

	size_t resourcesOnMap = 0; // don't need?
};

