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
#include "Object.h"


class Map {
private:

	Object** field = nullptr;

	const size_t minMapSize = 1000;

	// symbols cnt in column (x)
	size_t mapLength = 0;

	// symbols cnt in line (y)
	size_t mapWidth = 0;

	//size_t resourcesOnMap = 0; // don't need?

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
		field = nullptr;
		ifstream in;
		in.open(fileName);
		if (!in.is_open()) {
			throw std::exception("Can't open the file.");
			return;
		}
		
		// symbols in str (mapWidth) cnt
		string width;
		std::getline(in, width);
		this->mapWidth = width.size();
		in.seekg(0, ios_base::beg);

		// strings (mapLength) cnt
		string str;
		this->mapLength = 0;
		while (std::getline(in, str)) {
			++(this->mapLength);
		}
		in.seekg(0, ios_base::beg);

		field = new Object* [mapLength];
		for (size_t i = 0; i < mapLength; ++i) {
			field[i] = new Object[mapWidth];
		}
		
		Object obj;
		for (size_t i = 0; i < mapLength; ++i) {
			if (!std::getline(in, str)) {
				if (str.size() < mapWidth || str.size() > mapWidth) {
					in.close();

					for (size_t i = 0; i < this->mapLength; ++i) {
						delete[] field[i];
						field[i] = nullptr;
					}
					delete[] field;
					field = nullptr;

					throw exception("Wrong file content. One of the strings has wrong length."); // ERROR: unexpected exception
					return;
				}
				else {
					for (size_t j = 0; j < str.size(); ++j) {
						obj = static_cast<Object>(str[j]);
						this->field[i][j] = obj;
					}
				}
			}
			else {
				in.close();
				throw exception("File read was not finished");
				return;
			}
		}
		in.close();
	}

	virtual ~Map() {
		for (size_t i = 0; i < this->mapLength; ++i) {
			delete[] field[i];
			field[i] = nullptr;
		}
		delete[] field;
		field = nullptr;
	}

	Object getObject(const Coordinates& coords) const {
		if (this->field == nullptr) throw exception("Can't get object. Field in map is nullptr.");
		if (coords.x >= mapLength || coords.y >= mapWidth) {
			throw exception("Can't get object from map. Incorrect coordinates.");
		}
		else {
			return this->field[coords.x][coords.y];
		}
	}

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
		if (coords.x > this->mapLength || coords.y > this->mapWidth) {
			throw std::exception("Wrong index in SetCell");
		}
		this->field[coords.x][coords.y] = obj;
	}
	void fill(const Object &obj) {
		for (size_t i = 0; i < mapLength; ++i) {
			for (size_t j = 0; j < mapWidth; ++j) {
				this->field[i][j] = obj;
			}
		}
	}

	Map operator=(const Map& other) {
		// cleaning mem
		for (size_t i = 0; i < mapLength; ++i) {
			delete[] field[i];
			field[i] = nullptr;
		}
		delete[] field;
		field = nullptr;

		// copying
		this->mapLength = other.mapLength;
		this->mapWidth = other.mapWidth;

		field = new Object* [mapLength];
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

};

