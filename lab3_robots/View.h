#pragma once

//#include "Map.h"
//#include "Robot.h"
#include "Explorer.h"
#include "Sapper.h"

#include <iostream>
#include <exception>

using namespace std;

class IView {
public:
	// one robot
	void virtual showMap(Robot* robot, const int& oneSideViewField) = 0;
	
	// two robots
	void virtual showMap(Explorer* WALLE, Sapper* EVE, const int& oneSideViewField) = 0;

};


class ConsoleView : public IView {
public:
	
	// TODO:
	// show robot in the center 

	// one robot
	void showMap(Robot* robot, const int& oneSideViewField) {
		for (size_t i = 0; i < oneSideViewField; ++i) {
			for (size_t j = 0; j < oneSideViewField; ++j) {

				// map end
				size_t x = 0, y = 0;
				if (robot->getCurrX() > i) x = robot->getCurrX() - i;
				else {
					cout << "  ";
					continue;
				}
				if (robot->getCurrY() > j) y = robot->getCurrY() - j;
				else {
					cout << "  ";
					continue;
				}

				if (robot->getMap()[x][y] == object::unknown) cout << "? ";
				else if (robot->getMap()[x][y] == object::apple) cout << "A ";
				else if (robot->getMap()[x][y] == object::bomb) cout << "B ";
				else if (robot->getMap()[x][y] == object::empty) cout << ". ";
				else if (robot->getMap()[x][y] == object::rock) cout << "# ";
			}
			cout << endl;
		}
	}

	// two robots
	void showMap(Explorer* WALLE, Sapper* EVE, const int& oneSideViewField) {
		for (size_t i = -oneSideViewField; i < oneSideViewField; ++i) {
			for (size_t j = oneSideViewField; j < oneSideViewField; ++j) {

				// x, y generation 
				size_t x = 0, y = 0;
				x = WALLE->getCurrX() + i;
				y = WALLE->getCurrY() + j;

				if (x == WALLE->getCurrX() && y == WALLE->getCurrY()) {
					cout << "E ";
					continue;
				}
				else if (x == EVE->getCurrX() && y == EVE->getCurrY()) {
					cout << "S ";
					continue;
				}
				
				// map edge
				if (x < 0) {
					cout << "  ";
					continue;
				}
				if (y < 0) {
					cout << "  ";
					continue;
				}
				

				/*
				// map end case
				if (WALLE->getCurrX() > i) x = WALLE->getCurrX() - i;
				else {
					cout << "  ";
					continue;
				}
				if (WALLE->getCurrY() > j) y = WALLE->getCurrY() - j;
				else {
					cout << "  ";
					continue;
				}
				*/

				// map display
				if (WALLE->getMap()[x][y] == object::unknown) cout << "? ";
				else if (WALLE->getMap()[x][y] == object::apple) cout << "A ";
				else if (WALLE->getMap()[x][y] == object::bomb) cout << "B ";
				else if (WALLE->getMap()[x][y] == object::empty) cout << ". ";
				else if (WALLE->getMap()[x][y] == object::rock) cout << "# ";
			}
			cout << endl;
		}
	}

};

