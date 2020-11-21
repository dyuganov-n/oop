#pragma once

#include "Robot.h"
//#include "Sapper.h"
#include "Mode.h"
#include "Map.h"

class Explorer : public Robot {
private:
	
	Map planet;
	Map* _map;

	//Sapper* sapper = nullptr;

	size_t resourcesOnMap = 0;

	size_t currX = 0;
	size_t currY = 0;

public:
	Explorer(const Map* _planet) { // Explorer(Sapper* s, const Map& _planet)
		//sapper = s;
		//planet = _planet;
		//_map = _planet;
		_map->clear();
	}

	//Explorer() {}

	// interface 
	size_t getCurrX() { return this->currX; }
	size_t getCurrY() { return this->currY; }
	void setCurrX(const size_t& x) { this->currX = x; }
	void setCurrY(const size_t& y) { this->currY = y; }
	object** getMap() { return this->_map.getMap(); }
	void move(const Direction& dir);

	//void setMode(const IMode& md); // scan or auto or manual

	// other
	void collect();
	void scan();
	


	void setLocation(const size_t& x, const size_t& y) {
		this->currX = x;
		this->currY = y;
	}

	Map* getMapPtr() { return &_map; }

	void scan() {
		//if(this->currX == )
	}

	

}

