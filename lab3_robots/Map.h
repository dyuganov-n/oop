#pragma once

#include <exception>

enum class object : char {
	rock = 'r',
	bomb = 'b',
	empty = 'e',
	apple = 'a',
	unknown = 'u'
};

class Map {
private:
	const size_t minMapSize = 1000;

	size_t mapLength;
	size_t mapWidth;
	object** _map;

public:
	Map() {
		mapLength = minMapSize;
		mapWidth = minMapSize;

		_map = new object* [mapLength];
		for (size_t i = 0; i < mapLength; ++i) {
			_map[i] = new object[mapWidth];
		}
		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				this->_map[i][j] = object::unknown;
			}
		}
	}

	Map(const size_t& length, const size_t& width) {
		mapLength = length;
		mapWidth = width;

		_map = new object * [mapLength];
		for (size_t i = 0; i < mapLength; ++i) {
			_map[i] = new object[mapWidth];
		}
		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				this->_map[i][j] = object::unknown;
			}
		}
	}

	virtual ~Map() {
		for (size_t i = 0; i < this->getMapLength(); ++i) {
			delete[] _map[i];
			_map[i] = nullptr;
		}
		delete[] _map;
		_map = nullptr;
	}

	object** getMap() { return this->_map; }
	size_t getMapLength() { return this->mapLength; }
	size_t getMapWidth() { return this->mapWidth; }

	void setCell(const size_t& x, const size_t& y, object obj) {
		try {
			if (x > this->mapLength || y > this->mapWidth) {
				throw std::exception("Wrong index in SetCell");
			}
			this->_map[x][y] = obj;
		}
		catch (const std::exception& e) { throw e; }
	}
	void fill(const object &obj) {
		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				this->_map[i][j] = obj;
			}
		}
	}
	void clear() {
		this->fill(object::unknown);
	}

	Map operator=(const Map& val) {
		// cleaning mem
		for (size_t i = 0; i < minMapSize; ++i) {
			delete[] _map[i];
			_map[i] = nullptr;
		}
		delete[] _map;
		_map = nullptr;

		// copying
		this->mapLength = val.mapLength;
		this->mapWidth = val.mapWidth;

		_map = new object * [mapLength];
		for (size_t i = 0; i < mapLength; ++i) {
			_map[i] = new object[mapWidth];
		}
		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				this->_map[i][j] = val._map[i][j];
			}
		}
		return *this;
	}

};

