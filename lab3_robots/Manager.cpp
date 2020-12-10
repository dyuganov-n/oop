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
		return { 0, 0 };
	}
	Object obj;
	for (size_t i = 0; i < map.getMapLength(); ++i) {
		for (size_t j = 0; j < map.getMapWidth(); ++j) {
			obj = map.getObject({ i, j });
			if (obj == Object::empty || obj == Object::apple) {
				if (repeater->isEmptyCell({ i, j })) return { i, j };
			}
		}
	}
	throw exception("Can't find empty place for robot.");
	return { 0, 0 };
}

void Manager::CreateExplorer() {
	Coordinates newCoords = FindEmptySpace(environment->getGlobalMap());
	IMode* newMode = IdlingMode::getInstance();
	Explorer* newExplorer = new Explorer(newCoords, repeater, environment);
	this->repeater->NotifyMove(newCoords, newCoords);
	this->robots.push_back({ newMode, newExplorer });
}

void Manager::CreateSapper() {
	if (robots.empty()) {
		throw exception("Can't create sapper. There is no explorers.");
	}
	else {
		Coordinates newCoords = FindEmptySpace(robots.at(0).second->getMap()); 
		IMode* newMode = IdlingMode::getInstance();
		Sapper* newSapper = new Sapper(robots.at(0).second->getMap(), newCoords, repeater, environment);
		this->repeater->NotifyMove(newCoords, newCoords);
		this->robots.push_back({ newMode, newSapper });
	}
}

/*
void Manager::handleCommand(ICommand* command) {
	command->execute();
	// sth else?
}*/
/*
void Manager::Step() {
	if (EnvironmentPtrIsNull()) throw exception("Manager can't make step. Environment pointer is nullptr.");
	if (RepeaterPtrIsNull()) throw exception("Manager can't make step. Repeater pointers is nullptr.");
	for (auto rbt : robots) {
		//ICommand* command = parser->parseCommand(robots);
		//handleCommand(command);
		//delete command;
	}
}*/

void Manager::ChangeExplorerMode(IMode* newMode) {
	for (auto& item : robots) {
		if (item.second->getRobotClass() == RobotClass::explorer) {
			item.first = newMode;
			return;
		}
	}
	throw exception("Can't change explorer mode. There are no explorers.");
}
