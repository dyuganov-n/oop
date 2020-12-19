#include "Mode.h"
#include "Command.h"

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

//vector<Coordinates> findWayToUnknCell(const Map& map, const Coordinates& start, const Object& objToFind) {
//	vector<Coordinates> result;
//	
//	const ptrdiff_t W = 12;         // ������ �������� ����
//	const ptrdiff_t H = 8;         // ������ �������� ����
//	const ptrdiff_t WALL = -1;         // ������������ ������
//	const ptrdiff_t BLANK = -2;         // ��������� ������������ ������
//
//	ptrdiff_t px[W * H], py[W * H];      // ���������� �����, ��������  ����
//	ptrdiff_t len;                       // ����� ����
//	ptrdiff_t grid[H][W];                // ������� ����
//
//	// ����� ������� lee() ������ grid �������� ���������� WALL � BLANK
//
//	const ptrdiff_t dy[4] = { 1, 0, -1, 0 };   // ��������, ��������������� ������� ������
//	const ptrdiff_t dx[4] = { 0, 1, 0, -1 };   // ������, �����, ����� � ������
//	ptrdiff_t d, y, x, k;
//	bool stop;
//
//	ptrdiff_t ax, ay, bx, by; // ����, ���������� ����� A � B
//	//if (grid[ay][ax] == WALL || grid[by][bx] == WALL) return false;  // ������ (ax, ay) ��� (bx, by) - �����
//
//	// ��������������� �����
//	d = 0;
//	grid[start.x][start.y] = 0;            // ��������� ������ �������� 0
//	do {
//		stop = true;               // ������������, ��� ��� ��������� ������ ��� ��������
//		for (x = 0; x < map.getMapLength(); ++x)
//			for (y = 0; y < map.getMapWidth(); ++y)
//				if (grid[x][y] == d)                         // ������ (x, y) �������� ������ d
//				{
//					for (k = 0; k < 4; ++k)                    // �������� �� ���� ������������ �������
//					{
//						int ix = x + dx[k], iy = y + dy[k];
//						if (ix >= 0 && ix < map.getMapLength() && iy >= 0 && iy < map.getMapWidth() &&
//							grid[ix][iy] == BLANK)
//						{
//							stop = false;              // ������� ������������ ������
//							grid[ix][iy] = d + 1;      // �������������� �����
//						}
//					}
//				}
//		d++;
//	//} while (!stop && grid[by][bx] == BLANK);
//	} while (!stop);
//
//
//	if (grid[by][bx] == BLANK) return {};  // ���� �� ������
//
//	// �������������� ����
//	ptrdiff_t len = grid[by][bx];            // ����� ����������� ���� �� (ax, ay) � (bx, by)
//	y = bx;
//	x = by;
//	d = len;
//	while (d > 0)
//	{
//		px[d] = y;
//		py[d] = x; // ���������� ������ (x, y) � ����
//		//result.push_back({ x, y });
//		d--;
//		for (k = 0; k < 4; ++k)
//		{
//			int iy = x + dx[k], ix = y + dy[k];
//			if (iy >= 0 && iy < H && ix >= 0 && ix < W &&
//				grid[iy][ix] == d)
//			{
//				y = y + dy[k];
//				x = x + dx[k];           // ��������� � ������, ������� �� 1 ����� � ������
//				break;
//			}
//		}
//	}
//	px[0] = ax;
//	py[0] = ay;                    // ������ px[0..len] � py[0..len] - ���������� ����� ����
//	return result;
//}

#include <unordered_map>
#include <queue>
using namespace std;

vector<pair<Coordinates, Object>> neighbors(const Coordinates& pos, const Map& _map) {
	vector<Coordinates> neighbors = {
		{pos.x - 1, pos.y},
		{pos.x + 1, pos.y},
		{pos.x, pos.y - 1},
		{pos.x, pos.y + 1}
	};
	for (size_t i = 0; i < neighbors.size(); ++i) {
		const Coordinates& elem = neighbors.at(i);
		if (elem.x < 0 || elem.x >= _map.getMapLength() || 
			elem.y < 0 || elem.y >= _map.getMapWidth()) 
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

//vector<Coordinates> findWayToCell(const Map& _map, const Coordinates& start, const Object& objToFind) {
//	
//	queue<Coordinates> frontier;
//	frontier.push(start);
//	unordered_map<Coordinates, bool> visited;
//	visited[start] = true;
//	Coordinates current;
//
//	bool stop = false;
//
//	while (!frontier.empty() || stop) {
//		current = frontier.front();
//		for (auto& next : neighbors(current, _map)) {
//			if (!visited.at(next.first)) {
//				frontier.push(next.first);
//				visited[next.first] = true;
//				if (next.second == objToFind) {
//					stop = true;
//					break;
//				}
//			}
//		}
//	}
//}

void ScanMode::invokeCommand(IRobot* robot) {
	if (robot == nullptr) {
		throw exception("Scan mode error. Robot is nullptr.");
	}
	else if (!dynamic_cast<Explorer*>(robot)) {
		throw exception("Scan mode error. Robot is not Explorer.");
	}
	else {
		Explorer* explorer = dynamic_cast<Explorer*>(robot);
		if (this->stepsNumber == 0) return;
		else {
			// logics for explorer 
			
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