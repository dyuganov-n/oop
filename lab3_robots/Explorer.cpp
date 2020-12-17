#include "Explorer.h"

Explorer::Explorer(const Coordinates& startPosition, Repeater* rep, Environment* env, const size_t& _id ) {
	this->position = startPosition;
	this->repeater = rep;
	this->environment = env;
	this->id = _id;
}

Explorer::~Explorer() {
	this->repeater = nullptr;
	this->environment = nullptr;
}

void Explorer::collect() {
	if (internalMap.getObject(position) == Object::apple) {
		if (environment->appleCollected(position)) {
			internalMap.setObject(position, Object::empty);
			repeater->NotifyCollect({ position.x, position.y });
		}
		else {
			throw exception("Explorer collect error. Global map has no apple at this position.");
		}
	}
}

void Explorer::_scan(const Coordinates& objCoords, vector<pair<Coordinates, Object>>& scanResult) {
	Object obj = this->environment->getObjectForRobot(objCoords);
	scanResult.push_back({ objCoords, obj });
	this->internalMap.setObject(objCoords, obj); // use old coords!!!
}

void Explorer::scan() {
	vector<pair<Coordinates, Object>> scanResult;
	vector<Coordinates> coords = {
		{ position.x, position.y - 1 }, // left
		{ position.x, position.y + 1 }, // right
		{ position.x - 1, position.y }, // up
		{ position.x + 1, position.y }, // down
		position						// curr position
	};

	repeater->NotifyScan(environment->scan(coords)); 
	internalMap.setObject(environment->scan(coords));


	// ________________________
	//for (size_t i = 0; i < coords.size(); ++i) {
	//	if (environment->isOverGlobalMap(coords.at(i))) {
	//		coords.erase(coords.begin() + i);
	//	}
	//}
	//Coordinates oldPosition(position);
	//Coordinates newRobotsMapZero = environment->getRobotsZeroPoint();
	//bool changeCoordX = false, changeCoordY = false;
	//for (const auto& item : coords) {
	//	if (!environment->isOverGlobalMap(item)) {
	//		if (item.x < 0) {
	//			changeCoordX = true;
	//		}
	//		if (item.y < 0) {
	//			changeCoordY = true;
	//		}
	//	}
	//}
	////if (changeCoordX) {
	////	position.x += internalMap.getMapLength();
	////	newRobotsMapZero.x -= internalMap.getMapLength();
	////}
	////if (changeCoordY) {
	////	position.y += internalMap.getMapWidth();
	////	newRobotsMapZero.y -= internalMap.getMapWidth();
	////}
	//if (changeCoordX || changeCoordY) {
	//	vector<pair<Coordinates, Object>> scannedPoints = environment->scan(coords);
	//	for (auto& item : scannedPoints) { // дойти до расширения карты и остановиться
	//		if (item.first.x < 0) {
	//			position.x += internalMap.getMapLength();
	//			newRobotsMapZero.x -= internalMap.getMapLength();
	//		}
	//		if (item.first.y < 0) {
	//			position.y += internalMap.getMapWidth();
	//			newRobotsMapZero.y -= internalMap.getMapWidth();
	//		}
	//		internalMap.setObject(item.first, item.second);
	//		break;
	//	}
	//	for (auto& item : scannedPoints) { // изменить координаты и записать в ответ
	//		if (changeCoordX) {
	//			item.first.x += internalMap.getMapLength();
	//		}
	//		if (changeCoordY) {
	//			item.first.y += internalMap.getMapWidth();
	//		}
	//		internalMap.setObject(item.first, item.second); // err
	//		scanResult.push_back(item);
	//	}
	//}
	//else {
	//	for (auto& item : environment->scan(coords)) {
	//		internalMap.setObject(item.first, item.second);
	//		scanResult.push_back(item);
	//	}
	//}
	//this->environment->setRobotsMapZeroPoint(newRobotsMapZero);
	//this->repeater->NotifyMove(oldPosition, position);
	//this->repeater->NotifyScan(scanResult);
	
	// __________________________________
	//environment->scan(coords);
	//for (const auto& item : coords) {
	//	if (!environment->isOverGlobalMap(item)) {
	//		Coordinates oldPosition = position;
	//		Coordinates newRobotsMapZero = environment->getRobotsZeroPoint();
	//		bool changeLength = false, changeWidth = false;
	//		if (item.x < 0) {
	//			this->position.x += internalMap.getMapLength();
	//			newRobotsMapZero.x -= internalMap.getMapLength(); 
	//			changeLength = true;
	//		}
	//		if (item.y < 0) {
	//			this->position.y += internalMap.getMapWidth();
	//			newRobotsMapZero.y -= internalMap.getMapWidth();
	//			changeWidth = true;
	//		}
	//		_scan(item, scanResult);
	//		this->environment->setRobotsMapZeroPoint(newRobotsMapZero);
	//		if (changeWidth) {
	//			for (auto& i : newCoords) {
	//				i.y += internalMap.getMapWidth();
	//			}
	//		}
	//		if (changeLength) {
	//			for (auto& i : newCoords) {
	//				i.x += internalMap.getMapLength();
	//			}
	//		}
	//		Object obj = this->environment->getObjectForRobot(item);
	//		scanResult.push_back({ item, obj });
	//		this->internalMap.setObject(item, obj); // use old coords!!!
	//		this->repeater->NotifyMove(oldPosition, position);
	//	}
	//}
	//this->repeater->NotifyScan(scanResult);
}


