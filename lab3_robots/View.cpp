#include "View.h"

void ConsoleView::displayMap(Manager* mngr, const int& oneSideViewField, const ViewMode& VMode) {
	if (mngr->getRobots().empty()) throw exception("Can't display map. Robots vector is empty.");
	IRobot* mainRobot = mngr->getRobots().at(0).second;
	if (mainRobot == nullptr) throw exception("Can't display map. Main robot pointer is nullptr.");
	
	system("cls");

	//ptrdiff_t x = 0, y = 0;
	Coordinates tmp;
	Object obj = Object::unknown;

	for (ptrdiff_t i = -oneSideViewField; i < oneSideViewField; ++i) {
		for (ptrdiff_t j = -oneSideViewField; j < oneSideViewField; ++j) {

			tmp.x = mainRobot->getPosition().x + i;
			tmp.y = mainRobot->getPosition().y + j;

			if (mngr->getEnvironment()->isOverGlobalMap(tmp)) {
				cout << "  ";
				continue;
			}

			if (robotInCell(mngr->getRobots(), tmp)) {
				for (auto item : mngr->getRobots()) {
					if (item.second->getPosition().x == tmp.x && item.second->getPosition().y == tmp.y) {
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

			if (tmp.x >= mainRobot->getMap().getMapLength() || tmp.y >= mainRobot->getMap().getMapWidth()) {
				cout << ", ";
				continue;
			}

			if (VMode == ViewMode::GlobalMap) {
				obj = mngr->getEnvironment()->getObject(tmp);
			}
			else if (VMode == ViewMode::LocalMap) {
				obj = mngr->getRobotsMap().getObject(tmp);
			}

			if (obj == Object::unknown) std::cout << "? ";
			else if (obj == Object::apple) std::cout << "@ ";
			else if (obj == Object::bomb) std::cout << "x ";
			else if (obj == Object::empty) std::cout << ". ";
			else if (obj == Object::rock) std::cout << "# ";
			else cout << "? ";

		}
		std::cout << std::endl;
	}
	cout << "Apples collected: " << mngr->getEnvironment()->getCollectedCnt() << endl;
}

bool ConsoleView::robotInCell(vector<pair<IMode*, IRobot*>>& robots, const Coordinates &coords) {
	for (auto item : robots) {
		if (item.second->getPosition().x == coords.x && item.second->getPosition().y == coords.y) {
			return true;
		}
	}
	return false;
}