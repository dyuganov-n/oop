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
	for (ptrdiff_t i = 0; i < map.getMapLength(); ++i) {
		for (ptrdiff_t j = 0; j < map.getMapWidth(); ++j) {
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
	Coordinates newCoords = FindEmptySpace(environment->getGlobalMap());
	IMode* newMode = IdlingMode::getInstance();
	Explorer* newExplorer = new Explorer(newCoords, repeater, environment);
	this->repeater->NotifyCreated(newCoords);
	this->robots.push_back({ newMode, newExplorer });
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
			Sapper* newSapper = new Sapper(robots.at(0).second->getMap(), newCoords, repeater, environment);
			this->repeater->NotifyCreated(newCoords);
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

void Manager::ChangeExplorerMode(IMode* newMode) {
	for (auto& item : robots) {
		if (item.second->getRobotClass() == RobotClass::explorer) {
			item.first = newMode;
			return;
		}
	}
	throw exception("Can't change explorer mode. There are no explorers.");
}
