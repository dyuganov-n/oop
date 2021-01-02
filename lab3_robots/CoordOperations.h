#pragma once

#include "Coordinates.h"

bool operator==(const Coordinates& first, const Coordinates& second) {
	if (first.x == second.x && first.y == second.y) {
		return true;
	}
	return false;
}

bool operator!=(const Coordinates& first, const Coordinates& second) {
	if (first == second) return false;
	else return true;
}

bool operator<(const Coordinates& first, const Coordinates& second) {
	if (first.x < second.x) {
		if (first.y < second.y) {
			return true;
		}
		return false;
	}
	if (first.y < second.y) {
		return true;
	}
	return false;
}