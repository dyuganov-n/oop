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
	virtual void showMap(Manager* mngr, const int& oneSideViewField) = 0;
};

class ConsoleView : public IView {
public:
	void showMap(Manager* mngr, const int& oneSideViewField) {
		IRobot* mainRobot = mngr->getRobots()[0];

		for (ptrdiff_t i = -oneSideViewField; i < oneSideViewField; ++i) {
			for (ptrdiff_t j = -oneSideViewField; j < oneSideViewField; ++j) {

				// x, y generation 
				ptrdiff_t x = 0, y = 0;
				x = static_cast<ptrdiff_t>(mainRobot->getCoordinates().x) + i;
				y = static_cast<ptrdiff_t>(mainRobot->getCoordinates().y) + j;

				// point is robot check
				for (auto item : mngr->getRobots()) {
					if (item->getCoordinates().x == x && item->getCoordinates().y == y) {
						if (item->getRobotClass() == RobotClass::explorer) {
							std::cout << "E ";
							continue;
						}
						else if (item->getRobotClass() == RobotClass::sapper) {
							std::cout << "S ";
							continue;
						}
					}
				}
				
				// map edge
				if (x < 0 || x > mngr->getRobotsMap()->getMapLength()) {
					std::cout << "  ";
					continue;
				}
				if (y < 0 || y > mngr->getRobotsMap()->getMapWidth()) {
					std::cout << "  ";
					continue;
				}				
				
				// map display
				if (mngr->getRobotsField()[x][y] == Object::unknown) std::cout << "? ";
				else if (mngr->getRobotsField()[x][y] == Object::apple) std::cout << "A ";
				else if (mngr->getRobotsField()[x][y] == Object::bomb) std::cout << "B ";
				else if (mngr->getRobotsField()[x][y] == Object::empty) std::cout << ". ";
				else if (mngr->getRobotsField()[x][y] == Object::rock) std::cout << "# ";
			}
			std::cout << std::endl;
		}
	}
};

