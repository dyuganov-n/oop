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
	
	in.close();
	in.open(fileName);

	field = new Object * [mapLength];
	for (size_t i = 0; i < mapLength; ++i) {
		field[i] = new Object[mapWidth];
	}

	Object obj;
	for (size_t i = 0; i < mapLength; ++i) {
		if (std::getline(in, str)) {
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

string Map::getStringCoords(const Coordinates& coords) const  {
	string result = "Coordinates are: (";
	result += to_string(coords.x);
	result += ", ";
	result += to_string(coords.y);
	result += ").";
	return result;
}

Object Map::getObject(const Coordinates& coords) const {
	if (this->field == nullptr) {
		throw exception("Can't get object. Field in map is nullptr.");
		return Object::unknown;
	}
	if (coords.x < 0 || coords.x >= static_cast<ptrdiff_t>(mapLength) || 
		coords.y < 0 || coords.y >= static_cast<ptrdiff_t>(mapWidth)) {
		//return Object::unknown;
		string massage = "Map getObject error: incorrect coordinates. " + getStringCoords(coords);
		throw exception(massage.c_str());
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
	if (newField == nullptr) {
		throw exception("Fill new field in class Map error. NewField is nullptr.");
	}
	for (size_t i = 0; i < length; ++i) {
		for (size_t j = 0; j < width; ++j) {
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

void Map::_setObject(const Coordinates& coords, Object obj) {
	if (coords.x < 0 || coords.x >= static_cast<ptrdiff_t>(mapLength) ||
		coords.y < 0 || coords.y >= static_cast<ptrdiff_t>(mapWidth)) {
		throw exception("Set object error. Wrong coordinates.");
	}
	else {
		this->field[coords.x][coords.y] = obj;
	}
}

// return true, if expansion needed
bool Map::setObject(vector<pair<Coordinates, Object>> objects) {
	size_t newLength = mapLength, newWidth = mapWidth;

	// expansion need check
	bool changeCoordX = false, changeCoordY = false;
	bool notEnoughSpaceX = false, notEnoughSpaceY = false;
	for (auto& item : objects) {
		if (item.first.x < 0) {
			changeCoordX = true;
			notEnoughSpaceX = true;
		}
		if (item.first.y < 0) {
			changeCoordY = true;
			notEnoughSpaceY = true;
		}
		if(item.first.x >= mapLength) notEnoughSpaceX = true;
		if(item.first.y >= mapWidth) notEnoughSpaceY = true;
	}
	
	// simple case
	if (!(notEnoughSpaceX || notEnoughSpaceY)) {
		for (const auto& item : objects) {
			_setObject(item.first, item.second);
		}
		return false;
	}
	else {// expansion case
		if (notEnoughSpaceX) {
			newLength *= 2;
		}
		if (notEnoughSpaceY) {
			newWidth *= 2;
		}

		Object** newField = createField(newLength, newWidth);
		fillNewField(newField, Object::unknown, newLength, newWidth);

		if (changeCoordX && changeCoordY) {
			copyOldFieldToNew(newField, mapLength, mapWidth);
		}
		else if (changeCoordX) {
			copyOldFieldToNew(newField, mapLength, 0);
		}
		else if (changeCoordY) {
			copyOldFieldToNew(newField, 0, mapWidth);
		}
		else {
			copyOldFieldToNew(newField, 0, 0);
		}

		deleteCurrField();
		this->field = newField;
		newField = nullptr;
		this->mapLength = newLength;
		this->mapWidth = newWidth;

		for (auto& item : objects) {
			if (changeCoordX) item.first.x += mapLength/2;
			if (changeCoordY) item.first.y += mapWidth/2;
			_setObject(item.first, item.second);
		}
		return true;
	}

}

// return true, if expansion needed
bool Map::setObject(const Coordinates& coords, Object obj) {
	if (mapLength == 0 || mapWidth == 0) {
		throw exception("SetObject error. Map legth or width equal 0."); 
		return false;
	}
	if (coords.x >= static_cast<ptrdiff_t>(mapLength) || coords.x < 0 || 
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

		this->field[coords.x][coords.y] = obj;
		return true;
	}
	else {
		this->field[coords.x][coords.y] = obj;
		return false;
	}
	
}

// fill all cells
void Map::fill(const Object& obj) {
	for (size_t i = 0; i < mapLength; ++i) {
		for (size_t j = 0; j < mapWidth; ++j) {
			this->field[i][j] = obj;
		}
	}
}

Map& Map::operator=(const Map& other) {
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