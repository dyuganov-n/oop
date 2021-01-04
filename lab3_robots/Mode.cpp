#include "Mode.h"
#include "CoordOperations.h"

#include <map>
#include <queue>
using namespace std;

ManualMode* ManualMode::p_instance = NULL;
IdlingMode* IdlingMode::p_instance = NULL;
ScanMode* ScanMode::p_instance = NULL;
AutoMode* AutoMode::p_instance = NULL;

ManualMode* ManualMode::getInstance() {
	if (!p_instance)
		p_instance = new ManualMode();
	return p_instance;
}
IdlingMode* IdlingMode::getInstance() {
	if (!p_instance)
		p_instance = new IdlingMode();
	return p_instance;
}
ScanMode* ScanMode::getInstance() {
	if (!p_instance) {
		p_instance = new ScanMode();
	}
	return p_instance;
}
AutoMode* AutoMode::getInstance() {
	if (!p_instance)
		p_instance = new AutoMode();
	return p_instance;
}

void IdlingMode::invokeCommand(IRobot* robot) {
	if (robot == nullptr) {
		throw exception("Auto mode error. Robot is nullptr.");
	}
	else {
		robot->idling();
	}
}

void ManualMode::invokeCommand(IRobot* robot) {
	if (robot == nullptr) {
		throw exception("Manual mode error. Robot is nullptr.");
		return;
	}
	else if (!dynamic_cast<Explorer*>(robot)) {
		throw exception("Manual mode error. Robot is not Explorer.");
		return;
	}
	else {
		Explorer* explorer = dynamic_cast<Explorer*>(robot);
		switch (action) {
		case ManualModeAction::collect:
			explorer->collect();
			this->action = ManualModeAction::unknown;
			return;

		case ManualModeAction::scan:
			explorer->scan();
			this->action = ManualModeAction::unknown;
			return;

		case ManualModeAction::move:
			if (direction == Direction::unknown) {
				throw exception("ManualMode error. Move direction was not defined.");
				return;
			}
			else {
				explorer->move(direction);
				this->direction = Direction::unknown;
				return;
			}

		default:
			throw exception("ManualMode error. Action was not defined.");
			return;
		}
	}
}

vector<pair<Coordinates, Object>> neighbors(const Coordinates& pos, const Map& _map, const Environment& env) {
	vector<Coordinates> neighbors = {
		{pos.x - 1, pos.y},
		{pos.x + 1, pos.y},
		{pos.x, pos.y - 1},
		{pos.x, pos.y + 1}
	};
	for (size_t i = 0; i < neighbors.size(); ++i) {
		const Coordinates& elem = neighbors.at(i);
		if (elem.x < 0 || elem.x >= static_cast<ptrdiff_t>(_map.getMapLength()) || 
			elem.y < 0 || elem.y >= static_cast<ptrdiff_t>(_map.getMapWidth()) ||
			env.isOverGlobalMap(elem))
		{
			neighbors.erase(neighbors.begin() + i);
		}
	}
	vector<pair<Coordinates, Object>> result;
	for (const auto& item : neighbors) {
		result.push_back({ item, _map.getObject(item) });
	}
	return result;
}

Coordinates finalPointSearch(const Map& _map, const Coordinates& start, const Object& objToFind, const Environment& env) {
	queue<Coordinates> frontier;
	map<Coordinates, bool> visited;
	Coordinates current, final = start;

	frontier.push(start);
	visited[start] = true;
	bool wayFound = false, finalPointFound = false;

	// search final point
	while (!frontier.empty()) {
		current = frontier.front();
		frontier.pop();

		if (_map.getObject(current) == objToFind) {
			final = current;
			break;
		}

		for (auto& next : neighbors(current, _map, env)) {
			if (!visited.count(next.first)) {
				frontier.push(next.first);
				visited[next.first] = true;
			}
		}
	}

	return final;
}

vector<Coordinates> findPathToCell (const Map& _map, const Coordinates& start, const Environment& env, const Object& objToFind, const vector<Object>& barrierObjs) {

	if (start.x < 0 || start.x >= _map.getMapLength() || start.y < 0 || start.y >= _map.getMapWidth()) {
		throw exception("Searching path to cell error. Wrong start point coordinates.");
	}

	queue<Coordinates> frontier;
	map<Coordinates, Coordinates> cameFrom; 
	map<Coordinates, bool> visited;	
	Coordinates current, final;

	frontier.push(start);
	visited[start] = true;
	cameFrom[start] = start;
	bool wayFound = false;

	// search final point
	final = finalPointSearch(_map, start, objToFind, env);
	if (final == start) return {};	

	// не учитываются стены и др преграды на пути
	// не может прийти к точке в углу
	// не доходит до точки вообще

	// looking for path to final point
	while (!frontier.empty()) {
		current = frontier.front();
		frontier.pop();

		if (final == current) {
			wayFound = true;
			break;
		}

		for (auto& next : neighbors(current, _map, env)) {
			/*for (const auto& item : barrierObjs) {
				if (next.second == item) continue;
			}*/
			if (!cameFrom.count(next.first)) {
				frontier.push(next.first);
				visited[next.first] = true;
				cameFrom[next.first] = current;
			}
		}
	}

	if (!wayFound) {
		return {};
	}

	// build the way
	vector<Coordinates> result;
	current = final;
	result.push_back(current);
	
	while (current != start) {
		current = cameFrom.at(current);
		result.push_back(current);
	}

	reverse(result.begin(), result.end());

	return result;
}

void ScanMode::invokeCommand(IRobot* robot) {
	if (robot == nullptr) {
		throw exception("Scan mode error. Robot is nullptr.");
	}
	if (!dynamic_cast<Explorer*>(robot)) {
		throw exception("Scan mode error. Robot is not Explorer.");
	}

	Explorer* explorer = dynamic_cast<Explorer*>(robot);
	if (this->stepsNumber == 0) return;

	// logics for explorer 
	while (stepsNumber > 0) {
		explorer->scan();

		vector<Coordinates> path;
		path = findPathToCell(explorer->getMap(), explorer->getPosition(), *(robot->getEnvironment()), Object::unknown, { Object::bomb, Object::rock });
		if (path.empty()) return;

		if (stepsNumber <= path.size()) {
			for (size_t i = 0; i < stepsNumber; ++i) {
				explorer->move(path.at(i));
				explorer->scan();
			}
			break;
		}
		else {
			for (size_t i = 0; i < path.size(); ++i) {
				explorer->move(path.at(i));
				explorer->scan();
			}
			stepsNumber -= path.size();
		}
	}
}

void AutoMode::invokeCommand(IRobot* robot) {
	if (robot == nullptr) {
		throw exception("Auto mode error. Robot is nullptr.");
	}
	else {
		if (dynamic_cast<Explorer*>(robot)) {
			Explorer* explorer = dynamic_cast<Explorer*>(robot);
			// logics for explorer
		}
		else {
			Sapper* sapper = dynamic_cast<Sapper*>(robot);
			// logics for sapper
		}
	}
}


