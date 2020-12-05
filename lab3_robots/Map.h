#pragma once

/// TODO:
/// dynamic externtion
/// int coordinates 

#include <exception>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#include "Coordinates.h"

enum class Object : char {
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
	Map(const string& fileName) {
		size_t stringsCnt = 0;
		size_t symbolsInStrCnt = 0;
		char c;

		ifstream in(fileName);
		if (!in.is_open()) throw std::exception("Some problems with opening a file");

		// symbols cnt
		in >> c;
		while ((c != '\n') || (c != EOF)) {
			if (c != ' ') ++symbolsInStrCnt;
		}
		in.seekg(0, ios_base::beg); // in.seekg(0, std::ios::beg);

		// strings cnt
		in >> c;
		while (c != EOF) {
			if (c == '\n') ++stringsCnt; // begin with 1?
		}
		in.seekg(0, ios_base::beg); // in.seekg(0, std::ios::beg);

		this->mapLength = stringsCnt;
		this->mapWidth = symbolsInStrCnt;

		field = new Object * [mapLength];
		for (size_t i = 0; i < mapLength; ++i) {
			field[i] = new Object[mapWidth];
		}

		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				in >> c;
				this->field[i][j] = static_cast<Object>(c);
			}
		}
		in.close();
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

	size_t getMapLength() const { return this->mapLength; }
	size_t getMapWidth() const { return this->mapWidth; }

	/*
	void resourceFound() { ++resourcesOnMap; }
	void resourceCollected() { 
		if (resourcesOnMap) --resourcesOnMap;
		else throw exception("All resources of the map were collected");
	}
	const size_t& getResourcesOnMap() const { return this->resourcesOnMap; }
	*/

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

