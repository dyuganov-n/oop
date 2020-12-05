#pragma once

//using namespace std;

struct Coordinates {
	size_t x = 0;
	size_t y = 0;
};

// if problems with operator<, just dont use sorted containers



/*
bool operator==(const Coordinates& l, const Coordinates& r) {
	if (l.x == r.x) {
		if (l.y == r.y) {
			return true;
		}
	}
	else {
		return false;
	}
}
*/