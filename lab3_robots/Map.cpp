#include "Map.h"

Map::Map() {
	mapLength = minMapSize;
	mapWidth = minMapSize;

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

Map::Map(const size_t& length, const size_t& width) {
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

Map::Map(const string& fileName) {
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

	field = new Object * [mapLength];
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
				throw exception("Wrong file content. One of the strings has wrong length.");
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

Map::~Map() {
	for (size_t i = 0; i < this->mapLength; ++i) {
		delete[] field[i];
		field[i] = nullptr;
	}
	delete[] field;
	field = nullptr;
}

Object Map::getObject(const Coordinates& coords) const {
	if (this->field == nullptr) throw exception("Can't get object. Field in map is nullptr.");
	if (coords.x >= static_cast<ptrdiff_t>(mapLength) || coords.y >= static_cast<ptrdiff_t>(mapWidth)) {
		return Object::unknown;
		//throw exception("Can't get object from map. Incorrect coordinates.");
	}
	else {
		return this->field[coords.x][coords.y];
	}
}

void Map::deleteCurrField() {
	for (size_t i = 0; i < mapLength; ++i) {
		delete[] field[i];
		field[i] = nullptr;
	}
	delete[] field;
	field = nullptr;
}

Object** Map::createField(const size_t& length, const size_t& width) {
	Object** newField = new Object* [length];
	for (size_t i = 0; i < length; ++i) {
		newField[i] = new Object[width];
	}
	return newField;
}

void Map::fillNewField(Object** newField, const Object& obj, const size_t& length, const size_t& width) {
	for (size_t i = 0; i < mapLength; ++i) {
		for (size_t j = 0; j < mapWidth; ++j) {
			newField[i][j] = obj;
		}
	}
}

void Map::copyOldFieldToNew(Object** newField, const size_t& offsetLength, const size_t& offsetWidth) {
	if (newField == nullptr) {
		throw exception("Copy old field to new in class Map error. NewField is nullptr.");
	}
	for (size_t i = 0; i < mapLength; ++i) {
		for (size_t j = 0; j < mapWidth; ++j) {
			newField[i + offsetLength][j + offsetWidth] = this->field[i][j];
		}
	}
}

void Map::setObject(const Coordinates& coords, Object obj) {
	if (mapLength == 0 || mapWidth == 0) {
		throw exception("SetObject error. Map legth or width equal 0."); 
	}
	else if(coords.x >= static_cast<ptrdiff_t>(mapLength) || coords.x < 0 || 
			coords.y >= static_cast<ptrdiff_t>(mapWidth)  || coords.y < 0) {

		size_t newLength = mapLength, newWidth = mapWidth;
		bool needLengthOffset = false, needWidthOffset = false;
		if (coords.x >= static_cast<ptrdiff_t>(mapLength)) {
			newLength = this->mapLength * 2;
		}
		else if (coords.x < 0) {
			newLength = this->mapLength * 2;
			needLengthOffset = true;
		}
		if(coords.y >= static_cast<ptrdiff_t>(mapWidth)){
			newWidth = this->mapWidth * 2;
		}
		else if (coords.y < 0) {
			newWidth = this->mapLength * 2;
			needWidthOffset = true;
		}

		Object** newField = createField(newLength, newWidth);
		fillNewField(newField, Object::unknown, newLength, newWidth);

		if (needLengthOffset && needWidthOffset) {
			copyOldFieldToNew(newField, mapLength, mapWidth);
		}
		else if (needWidthOffset) {
			copyOldFieldToNew(newField, 0, mapWidth);
		}
		else if (needLengthOffset) {
			copyOldFieldToNew(newField, mapLength, 0);
		}
		else {
			copyOldFieldToNew(newField, 0, 0);
		}
		
		deleteCurrField();
		this->mapLength = newLength;
		this->mapWidth = newWidth;
		this->field = newField;
		newField = nullptr;
	}
	this->field[coords.x][coords.y] = obj;
}

void Map::fill(const Object& obj) {
	for (size_t i = 0; i < mapLength; ++i) {
		for (size_t j = 0; j < mapWidth; ++j) {
			this->field[i][j] = obj;
		}
	}
}

Map Map::operator=(const Map& other) {
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