#include "Sapper.h"

Sapper::Sapper(const Map& _map, const Coordinates& startPosition, Repeater* rep, Environment* env) {
	this->internalMap = _map;
	position = startPosition;
	this->environment = env;
	this->repeater = rep;
}

Sapper::~Sapper() {
	this->environment = nullptr;
	this->repeater = nullptr;
}

void Sapper::defuse() {
	updateMap();
	if (internalMap.getObject(position) == Object::bomb) {
		internalMap.setObject(position, Object::empty);
		repeater->NotifyDefuse(position);
		this->environment->bombDefused(position);
	}
}