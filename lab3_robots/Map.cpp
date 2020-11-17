#include "Map.h"


Map Map::operator=(const Map& val) {
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

	 _map = new object* [mapLength];
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