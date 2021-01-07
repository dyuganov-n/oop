#pragma once

#include "Coordinates.h"


bool operator==(const Coordinates& first, const Coordinates& second) {
	if (first.x == second.x && first.y == second.y) return true;
	return false;
}

bool operator!=(const Coordinates& first, const Coordinates& second) {
	if (first == second) return false;
	return true;
}

bool operator<(const Coordinates& first, const Coordinates& second) {
	if (first.x != second.x) return first.x < second.x;
	return first.y < second.y;
}

