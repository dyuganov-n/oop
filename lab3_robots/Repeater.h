#pragma once

#include <map>
#include <vector>

#include "Robot.h"
using std::pair;
using std::vector;


class Repeater {
private:
	vector<pair<Coordinates, Object>> changes;
	Manager* mngr = nullptr;

	//Repeater& operator=(Repeater& other) {}
public:
	Repeater() {}
	~Repeater() {}

	void notifyDefuse(const Coordinates& coords) {

	}
	void notifyScan(const Coordinates& center, 
					const std::map<Direction, Object>) {

	}
	void notifyCollect(const Coordinates& coords) {

	}

	vector<pair<Coordinates, Object>> getMapUpdates() {
		return this->changes;
	}

	
};

// singleton version
/*
class Repeater {
private:
	static Repeater* ptrInstance;
	Repeater(){}
	~Repeater(){}
	Repeater& operator=(Repeater& other) {}
public:
	static Repeater* getInstance() {
		if (!ptrInstance) {
			ptrInstance = new Repeater();
		}
		return ptrInstance;
	}
};
*/