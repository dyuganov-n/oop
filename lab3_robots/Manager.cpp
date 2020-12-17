#include "Manager.h"

Manager::Manager(const string& InputFileName) {
	this->environment = new Environment(InputFileName);
	this->repeater = new Repeater;
}

Manager::~Manager() {
	delete environment;
	environment = nullptr;

	delete repeater;
	repeater = nullptr;
}

Coordinates Manager::FindEmptySpace(const Map& map) const {
	if (repeater == nullptr) {
		throw exception("Can't find empty space. Repeater is nullptr.");
		//return { 0, 0 };
	}
	Object obj;
	for (ptrdiff_t i = 0; i < static_cast<ptrdiff_t>(map.getMapLength()); ++i) {
		for (ptrdiff_t j = 0; j < ptrdiff_t(map.getMapWidth()); ++j) {
			obj = map.getObject({ i, j });
			if (obj == Object::empty || obj == Object::apple) {
				if (repeater->isEmptyCell({ i, j })) return { i, j };
			}
		}
	}
	throw exception("Can't find empty place for robot.");
	//return { 0, 0 };
}

void Manager::CreateExplorer() {
	Coordinates globalCoords = FindEmptySpace(environment->getGlobalMap());
	const Coordinates robotStartCoords = { 0, 0 };
	IMode* newMode = IdlingMode::getInstance();
	Explorer* newExplorer = new Explorer(robotStartCoords, repeater, environment);
	this->repeater->NotifyRobotCreated(robotStartCoords);
	this->robots.push_back({ newMode, newExplorer });
	this->environment->setRobotsMapZeroPoint(globalCoords);
}

bool Manager::noSappersCreated() {
	for (const auto& item : robots) {
		if (item.second->getRobotClass() == RobotClass::sapper) {
			return false;
		}
	}
	return true;
}

bool Manager::explorerInManualMode() {
	if (dynamic_cast<ManualMode*>(this->robots.at(0).first)) {
		return true;
	}
	else {
		return false;
	}
}

void Manager::CreateSapper() {
	if (robots.empty()) {
		throw exception("Can't create sapper. There is no explorers.");
	}
	else if(noSappersCreated()) {
		if (explorerInManualMode()) {
			Coordinates newCoords = FindEmptySpace(robots.at(0).second->getMap());
			IMode* newMode = IdlingMode::getInstance();
			Sapper* newSapper = nullptr;
			for (const auto& item : robots) {
				if (item.second->getRobotClass() == RobotClass::explorer) {
					newSapper = new Sapper(item.second->getMap(), newCoords, repeater, environment);
				}
			}
			this->repeater->NotifyRobotCreated(newCoords);
			this->robots.push_back({ newMode, newSapper });
		}
		else {
			throw exception("CreateSapper error. Explorer mode is not manual.");
		}
	}
	else {
		throw exception("Can't create more than 1 sapper.");
	}
}

void Manager::DeleteSapper() {
	if (noSappersCreated()) {
		throw exception("Can't delete sapper. Sapper was not created.");
	}
	else {
		for (size_t i = 0; i < robots.size(); ++i) {
			if (robots.at(i).second->getRobotClass() == RobotClass::sapper) {
				repeater->NotifyRobotDeleted(robots.at(i).second->getCoordinates());
				Sapper* tmp = dynamic_cast<Sapper*>(robots.at(i).second);
				//tmp->~Sapper();
				robots.erase(robots.begin() + i);
				//delete tmp;											// ERROR HERE
				return;
			}
		}
	}
}

void Manager::ChangeExplorerMode(IMode* newMode) {
	for (auto& item : robots) {
		if (item.second->getRobotClass() == RobotClass::explorer) {
			item.first = newMode;
			return;
		}
	}
	throw exception("Can't change explorer mode. There are no explorers.");
}
