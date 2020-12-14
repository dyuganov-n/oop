#include "View.h"

void ConsoleView::displayMap(Manager* mngr, const int& oneSideViewField, const ViewMode& VMode) {
	if (mngr->getRobots().empty()) throw exception("Can't display map. Robots vector is empty.");
	IRobot* mainRobot = mngr->getRobots().at(0).second;
	if (mainRobot == nullptr) throw exception("Can't display map. Main robot pointer is nullptr.");
	
	system("cls");

	for (ptrdiff_t i = -oneSideViewField; i < oneSideViewField; ++i) {
		for (ptrdiff_t j = -oneSideViewField; j < oneSideViewField; ++j) {

			// x, y generation 
			ptrdiff_t x = 0, y = 0;
			x = static_cast<ptrdiff_t>(mainRobot->getCoordinates().x) + i;
			y = static_cast<ptrdiff_t>(mainRobot->getCoordinates().y) + j;

			// point is robot check
			if (robotInCell(mngr->getRobots(), x, y)) {
				for (auto item : mngr->getRobots()) {
					if (item.second->getCoordinates().x == x && item.second->getCoordinates().y == y) {
						if (item.second->getRobotClass() == RobotClass::explorer) {
							std::cout << "E ";
						}
						else if (item.second->getRobotClass() == RobotClass::sapper) {
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

			ptrdiff_t _x = 0, _y = 0;
			if (x >= 0) _x = static_cast<size_t>(x);
			else throw exception("Console view error. Coordinates can't be negative.");
			if (y >= 0) _y = static_cast<size_t>(y);
			else throw exception("Console view error. Coordinates can't be negative.");

			// map display
			if (VMode == ViewMode::GlobalMap) {
				const Object& obj = mngr->getEnvironment()->getObject({ _x, _y });
				if (obj == Object::unknown) std::cout << "? ";
				else if (obj == Object::apple) std::cout << "A ";
				else if (obj == Object::bomb) std::cout << "B ";
				else if (obj == Object::empty) std::cout << ". ";
				else if (obj == Object::rock) std::cout << "# ";
			}
			else if(VMode == ViewMode::LocalMap) {
				const Object& obj = mngr->getRobotsMap().getObject({ _x, _y });
				if (obj == Object::unknown) std::cout << "? ";
				else if (obj == Object::apple) std::cout << "A ";
				else if (obj == Object::bomb) std::cout << "B ";
				else if (obj == Object::empty) std::cout << ". ";
				else if (obj == Object::rock) std::cout << "# ";
			}
			else {
				throw exception("ConsoleView displayMap error. Unknown view mode.");
			}
		}
		std::cout << std::endl;
	}
	cout << "Apples collected: " << mngr->getEnvironment()->getCollectedCnt() << endl;
}

bool ConsoleView::robotInCell(vector<pair<IMode*, IRobot*>>& robots, ptrdiff_t x, ptrdiff_t y) {
	for (auto item : robots) {
		if (item.second->getCoordinates().x == x && item.second->getCoordinates().y == y) {
			return true;
		}
	}
	return false;
}