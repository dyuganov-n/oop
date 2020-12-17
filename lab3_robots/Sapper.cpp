#include "Sapper.h"

Sapper::Sapper(const Map& _map, const Coordinates& startPosition, Repeater* rep, Environment* env) {
	this->internalMap = _map;
	position = startPosition;
	this->environment = env;
	this->repeater = rep;
	//this->id = _id;
}

void Sapper::defuse() {
	updateMap();
	if (internalMap.getObject(position) == Object::bomb) {
		internalMap.setObject(position, Object::empty);
		repeater->NotifyDefuse(position);
		this->environment->bombDefused(position);
	}
}