#include "Sapper.h"

Sapper::Sapper(const Map& _map, const Coordinates& startPosition, Repeater* rep, Environment* env) {
	this->internalMap = _map;
	position = startPosition;
	this->environment = env;
	this->repeater = rep;
}

void Sapper::defuse() {
	if (internalMap.getObject(position) == Object::bomb) {
		internalMap.setObject(position, Object::empty);
		repeater->notifyDefuse(position);
		this->environment->bombDefused(position);
	}
}