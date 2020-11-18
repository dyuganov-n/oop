#pragma once

//#include "Map.h"
#include "Robot.h"
#include "Explorer.h"
#include "Sapper.h"

#include <iostream>
#include <exception>

using namespace std;

class View {
private:

public:

	void virtual setRobot(Robot* r) = 0;
	void virtual showMap() = 0;
	
};


class ConsoleView : public View {
public:

	void showMap(Robot* robot, const size_t& CellsInView) {
		for (size_t i = 0; i < CellsInView; ++i) {
			for (size_t j = 0; j < CellsInView; ++j) {

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

	void showMap(Explorer* WALLE, Sapper* EVE, const size_t& CellsInView) {
		for (size_t i = 0; i < CellsInView; ++i) {
			for (size_t j = 0; j < CellsInView; ++j) {

				// map end
				size_t x = 0, y = 0;
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

