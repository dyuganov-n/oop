#pragma once

struct Coordinates {
	ptrdiff_t x = 0;
	ptrdiff_t y = 0;
};

//bool operator==(const Coordinates& first, const Coordinates& second) {
//	if (first.x == second.x && first.y == second.y) {
//		return true;
//	}
//	return false;
//}
//
//bool operator!=(const Coordinates& first, const Coordinates& second) {
//	if (first == second) return false;
//	else return true;
//}
//
//bool operator<(const Coordinates& first, const Coordinates& second) {
//	if (first.x < second.x) {
//		return true;
//	}
//	if (first.y < second.y) {
//		return true;
//	}
//	return false;
//}
