#include "Mode.h"
#include "CoordOperations.h"

#include <map>
#include <unordered_map>
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

vector<pair<Coordinates, Object>> neighbors(const Coordinates& pos, const Map& _map, 
											const Environment& env, const vector<Object>& barrierObjs) {
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
			--i;
			continue;
		}
		for (const auto& item : barrierObjs) {
			if (_map.getObject(elem) == item) {
				neighbors.erase(neighbors.begin() + i);
				--i;
				break;
			}
		}
	}
	vector<pair<Coordinates, Object>> result;
	for (const auto& item : neighbors) {
		result.push_back({ item, _map.getObject(item) });
	}
	return result;
}

Coordinates finalPointSearch(const Map& _map, const Coordinates& start, const Object& objToFind,
							 const Environment& env, const vector<Object>& barrierObjs) {
	queue<Coordinates> frontier;
	map<Coordinates, Coordinates> cameFrom;
	vector<pair<Coordinates, Object>> _neighbors;
	Coordinates current;

	cameFrom[start] = start;
	frontier.push(start);

	// search final point
	while (!frontier.empty()) {
		current = frontier.front();
		frontier.pop();

		if (_map.getObject(current) == objToFind) {
			return current;
		}

		_neighbors = neighbors(current, _map, env, barrierObjs);
		for (auto& next : _neighbors) {
			if (!cameFrom.count(next.first)) {
				frontier.push(next.first);
				cameFrom[next.first] = current;
			}
		}
	}

	return start;
}

vector<Coordinates> buildPath(const Coordinates& start, const Coordinates& goal, const map<Coordinates, Coordinates>& cameFrom) {
	Coordinates current = goal;
	vector<Coordinates> result;
	result.push_back(current);

	while (current != start) {
		current = cameFrom.at(current);
		result.push_back(current);
	}
	reverse(result.begin(), result.end());

	return result;
}

vector<Coordinates> findPathToCell (const Map& _map, const Coordinates& start, const Environment& env, 
									const Object& objToFind, const vector<Object>& barrierObjs) {

	if (start.x < 0 || start.x >= _map.getMapLength() || 
		start.y < 0 || start.y >= _map.getMapWidth()) {
		throw exception("Searching path to cell error. Wrong start point coordinates.");
	}

	queue<Coordinates> frontier;
	map<Coordinates, Coordinates> cameFrom; 
	Coordinates current;

	frontier.push(start);
	cameFrom[start] = start;
	bool wayFound = false;

	// search final point
	Coordinates goal = finalPointSearch(_map, start, objToFind, env, barrierObjs);
	if (goal == start) return {};

	// search path to final point
	while (!frontier.empty()) {
		current = frontier.front();
		frontier.pop();

		if (goal == current) {
			wayFound = true;
			break;
		}

		for (auto& next : neighbors(current, _map, env, barrierObjs)) {
			if (!cameFrom.count(next.first)) {
				frontier.push(next.first);
				cameFrom[next.first] = current;
			}
		}
	}

	if (!wayFound) { return {}; }

	// build the way
	vector<Coordinates> result = buildPath(start, goal, cameFrom);

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

	vector<Coordinates> path;
	while (stepsNumber > 0) {
		explorer->scan();

		path = findPathToCell(explorer->getMap(), explorer->getPosition(), *(explorer->getEnvironment()), Object::unknown, { Object::bomb, Object::rock });
		if (path.empty()) return;
		else {
			path.erase(path.begin()); // delete current cell 
			path.pop_back(); // delete last cell (to scan it we don't step there & it can be bad cell)
		}

		if (stepsNumber < path.size()) {
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

void AutoMode::invokeCommand(Explorer* explorer, Sapper* sapper) {
	if (explorer == nullptr) {
		throw exception("Auto mode error. Robot is nullptr.");
		return;
	}

	bool allBombsDefused = false;
	vector<Coordinates> explorerPath, sapperPath;

	while (true) {
		// explorer
		if (!explorerPath.empty()) {
			explorer->move(explorerPath.at(0));
			explorerPath.erase(explorerPath.begin());
		}
		else {
			explorer->collect();
			explorerPath = findPathToCell(explorer->getMap(), explorer->getPosition(), *(explorer->getEnvironment()), Object::apple, { Object::bomb, Object::rock });
			if (explorerPath.empty()) return;
			explorerPath.erase(explorerPath.begin()); // delete current cell 
		}
		
		// sapper
		if (sapper != nullptr && !allBombsDefused) {
			if (!sapperPath.empty()) {
				sapper->move(sapperPath.at(0));
				sapperPath.erase(sapperPath.begin());
			}
			else {
				sapper->defuse();
				sapperPath = findPathToCell(sapper->getMap(), sapper->getPosition(), *(sapper->getEnvironment()), Object::bomb, { Object::rock });
				if (sapperPath.empty()) allBombsDefused = true;
				else sapperPath.erase(sapperPath.begin()); // delete current cell
			}
		}
	}
}

void AutoMode::invokeCommand(IRobot* robot) {
	if (robot->getRobotClass() != RobotClass::explorer) {
		throw exception("AutoMode::invokeCommand(IRobot* robot) error. Robot is not explorer.");
	}
	else {
		Explorer* explorer = dynamic_cast<Explorer*>(robot);
		invokeCommand(explorer, nullptr);
	}
}