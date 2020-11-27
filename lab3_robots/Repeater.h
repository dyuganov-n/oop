#pragma once

#include <map>
#include <vector>
using std::pair;
using std::vector;

#include "Map.h"

class Repeater {
private:
	vector<pair<Coordinates, Object>> changes;

public:
	Repeater() {}
	~Repeater() {}

	void notifyDefuse(const Coordinates& coords) {
		changes.push_back({ coords, Object::empty });
	}
	void notifyScan(const vector<pair<Coordinates, Object>>& objects) {
		for (const auto& item : objects) {
			this->changes.push_back(item);
		}
	}
	void notifyCollect(const Coordinates& coords) {
		changes.push_back({coords, Object::empty});
	}
	vector<pair<Coordinates, Object>> getMapUpdates() {
		return this->changes;
	}
};
