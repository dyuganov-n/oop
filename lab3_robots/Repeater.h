#pragma once

#include <map>
#include "Robot.h"

class Repeater {
private:
	vector<pair<Coordinates, object>> changes;

	Repeater& operator=(Repeater& other) {}
public:
	Repeater() {}
	~Repeater() {}

	void notifyDefuse(const Coordinates& coords) {

	}
	void notifyScan(const Coordinates& center, 
					const std::map<Direction, object>) {

	}
	void notifyCollect(const Coordinates& coords) {

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