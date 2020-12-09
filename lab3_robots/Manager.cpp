#include "Manager.h"

Manager::Manager(Parser* prsr) {
	this->parser = prsr;
	this->environment = new Environment(prsr->getMapFileName());
	this->repeater = new Repeater;
}

Manager::Manager() {
	this->environment = nullptr;
	this->parser = nullptr;
	this->repeater = new Repeater;
}

Manager::~Manager() {
	delete environment;
	environment = nullptr;

	delete repeater;
	repeater = nullptr;

	parser = nullptr;
}

bool Manager::internalPtrsNonNull() {
	if (parser == nullptr || environment == nullptr || repeater == nullptr) {
		return false;
	}
	return true;
}

vector<IRobot*> Manager::getRobots() {
	vector<IRobot*> result;
	for (auto r : robots) {
		result.push_back(r.second);
	}
	return result;
}

Coordinates Manager::findEmptySpace(const Map& map) const {
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


void Manager::createExplorer() {
	Coordinates newCoords = findEmptySpace(environment->getGlobalMap());
	IMode* newMode = new IdelingMode;
	Explorer* newExplorer = new Explorer(newCoords, repeater, environment);
	this->repeater->notifyMove(newCoords, newCoords);
	this->robots.push_back({ newMode, newExplorer });
}

void Manager::createSapper() {
	if (robots.empty()) throw exception("Can't create sapper. There is no explorers.");
	Coordinates newCoords = findEmptySpace(robots[0].second->getMap());
	IMode* newMode = new IdelingMode;
	Sapper* newSapper = new Sapper(robots[0].second->getMap(), newCoords, repeater, environment);
	this->repeater->notifyMove(newCoords, newCoords);
	this->robots.push_back({ newMode, newSapper });
}

void Manager::handleCommand(ICommand* command) {
	command->execute();
	// sth else?
}

void Manager::step() {
	if (!internalPtrsNonNull()) throw exception("Manager can't make step. Some of internal pointers is nullptr.");
	for (auto rbt : robots) {
		//this->updateGlobalMap();
		ICommand* command = parser->parseCommand(robots);
		handleCommand(command);
		delete command;
	}
}
