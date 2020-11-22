#pragma once

//#include "Map.h"
//#include "Robot.h"

#include "Sapper.h"
#include "Explorer.h"
#include "Manager.h"

#include <iostream>
#include <exception>

//using namespace std;

// апрашивает у менеджера карту с роботами
class IView {
public:
	// one robot
	void virtual showMap(IRobot* robot, const int& oneSideViewField) = 0;
	
	// two robots
	void virtual showMap(Explorer* WALLE, Sapper* EVE, const int& oneSideViewField) = 0;

	// could be version with main robot (in the center) + all other around
};


class ConsoleView : public IView {
private:
	Manager* mngr;

public:
	// two robots
	void showMap(const int& oneSideViewField) {
		Explorer* _explorer = mngr->getExplorer();
		Sapper* _sapper = mngr->getSapper();

		for (size_t i = -oneSideViewField; i < oneSideViewField; ++i) {
			for (size_t j = oneSideViewField; j < oneSideViewField; ++j) {

				// x, y generation 
				size_t x = 0, y = 0;
				x = _explorer->getCoordinates().x + i;
				y = _explorer->getCoordinates().y + j;

				// point is robot check
				if (x == _explorer->getCoordinates().x && y == _explorer->getCoordinates().y) {
					std::cout << "E ";
					continue;
				}
				else if (x == _sapper->getCoordinates().x && y == _sapper->getCoordinates().y) {
					std::cout << "S ";
					continue;
				}
				
				// map edge
				if (x < 0) {
					std::cout << "  ";
					continue;
				}
				if (y < 0) {
					std::cout << "  ";
					continue;
				}				

				// map display
				if (_explorer->getField()[x][y] == object::unknown) std::cout << "? ";
				else if (_explorer->getField()[x][y] == object::apple) std::cout << "A ";
				else if (_explorer->getField()[x][y] == object::bomb) std::cout << "B ";
				else if (_explorer->getField()[x][y] == object::empty) std::cout << ". ";
				else if (_explorer->getField()[x][y] == object::rock) std::cout << "# ";
			}
			std::cout << std::endl;
		}
	}

	// could be version with main robot (in the center) + all other around
};

