#include "Mode.h"

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
	if (!p_instance)
		p_instance = new ScanMode();
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
	}
	else if (!dynamic_cast<Explorer*>(robot)) {
		throw exception("Manual mode error. Robot is not Explorer.");
	}
	else {
		Explorer* explorer = dynamic_cast<Explorer*>(robot);
		// logics
	}
}

void ScanMode::invokeCommand(IRobot* robot) {
	if (robot == nullptr) {
		throw exception("Scan mode error. Robot is nullptr.");
	}
	else if (!dynamic_cast<Explorer*>(robot)) {
		throw exception("Scan mode error. Robot is not Explorer.");
	}
	else {
		Explorer* explorer = dynamic_cast<Explorer*>(robot);
		// logics
	}
}

void AutoMode::invokeCommand(IRobot* robot) {
	if (robot == nullptr) {
		throw exception("Auto mode error. Robot is nullptr.");
	}
	else {
		if (dynamic_cast<Explorer*>(robot)) {
			Explorer* explorer = dynamic_cast<Explorer*>(robot);
			// logics
		}
		else {
			Sapper* sapper = dynamic_cast<Sapper*>(robot);
			// logics
		}
	}
}