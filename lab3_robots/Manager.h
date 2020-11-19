#pragma once

#include "Sapper.h"
#include "Explorer.h"

// control interaction between sapper and explorer
class Manager {
private:
	Explorer* explorer;
	Sapper* sapper;

public:
	Manager(Explorer* ex, Sapper* sp) {
		this->explorer = ex;
		this->sapper = sp;
	}

	void setExplorer(Explorer* ex) { this->explorer = ex; }
	void setSapper(Sapper* sp) { this->sapper = sp; }

};

