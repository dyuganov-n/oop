#include "View.h"

void ConsoleView::displayMap(Manager* mngr, const int& oneSideViewField) {
	if (mngr->getRobots().empty()) throw exception("Can't display map. Robots vector is empty."); // exception triggered exit and error in ~Map. WHY!?
	IRobot* mainRobot = mngr->getRobots()[0];
	if (mainRobot == nullptr) throw exception("Can't display map. Main robot pointer is nullptr.");

	for (ptrdiff_t i = -oneSideViewField; i < oneSideViewField; ++i) {
		for (ptrdiff_t j = -oneSideViewField; j < oneSideViewField; ++j) {

			// x, y generation 
			ptrdiff_t x = 0, y = 0;
			x = static_cast<ptrdiff_t>(mainRobot->getCoordinates().x) + i;
			y = static_cast<ptrdiff_t>(mainRobot->getCoordinates().y) + j;

			// point is robot check
			if (robotInCell(mngr->getRobots(), x, y)) {
				for (auto item : mngr->getRobots()) {
					if (item->getCoordinates().x == x && item->getCoordinates().y == y) {
						if (item->getRobotClass() == RobotClass::explorer) {
							std::cout << "E ";
						}
						else if (item->getRobotClass() == RobotClass::sapper) {
							std::cout << "S ";
						}
					}
				}
				continue;
			}


			// map edge
			if (x < 0 || x > static_cast<ptrdiff_t>(mngr->getRobotsMap().getMapLength())) {
				std::cout << "  ";
				continue;
			}
			if (y < 0 || y > static_cast<ptrdiff_t>(mngr->getRobotsMap().getMapWidth())) {
				std::cout << "  ";
				continue;
			}

			size_t _x = 0, _y = 0;
			if (x >= 0) _x = static_cast<size_t>(x);
			else throw exception("Console view error. Coordinates can't be negative.");
			if (y >= 0) _y = static_cast<size_t>(y);
			else throw exception("Console view error. Coordinates can't be negative.");

			// map display
			if (mngr->getEnvironment()->getObject({ _x, _y }) == Object::unknown) std::cout << "? ";
			else if (mngr->getEnvironment()->getObject({ _x, _y }) == Object::apple) std::cout << "A ";
			else if (mngr->getEnvironment()->getObject({ _x, _y }) == Object::bomb) std::cout << "B ";
			else if (mngr->getEnvironment()->getObject({ _x, _y }) == Object::empty) std::cout << ". ";
			else if (mngr->getEnvironment()->getObject({ _x, _y }) == Object::rock) std::cout << "# ";
		}
		std::cout << std::endl;
	}
	cout << "Apples collected: " << mngr->getEnvironment()->getCollectedCnt() << endl;
}

bool ConsoleView::robotInCell(vector<IRobot*> robots, ptrdiff_t x, ptrdiff_t y) {
	for (auto item : robots) {
		if (item->getCoordinates().x == x && item->getCoordinates().y == y) {
			return true;
		}
	}
	return false;
}