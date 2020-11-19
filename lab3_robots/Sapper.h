#pragma once

#include "Robot.h"
#include "Explorer.h"

class Sapper : public Robot {
private:
	Explorer* expl;
	
	//Map _map;
	size_t currX = 0;
	size_t currY = 0;

public:

	Sapper(Explorer* ex) {
		this->expl = ex;
	}
	//Sapper();
	
	// interface 
	size_t getCurrX() { return this->currX; }
	size_t getCurrY() { return this->currY; }
	void setCurrX(const size_t& x) { this->currX = x; }
	void setCurrY(const size_t& y) { this->currY = y; }

	object** getMap() { return this->expl->getMap(); }

	void setMode(IMode& md); // on or off

	// other
	void setExploter(Explorer* e) { this->expl = e; }
	void defuse() {

	}
};

