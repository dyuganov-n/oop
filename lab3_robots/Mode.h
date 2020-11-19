#pragma once

class IMode {
public:
	void virtual setMode() = 0;
	//void virtual setCommand(const ICommand&) = 0;
};

//explorer modes
class ManualMode : public IMode {};

class ScanMode : public IMode {
	//void setCommand(const ICommand& c){	}
};
class AutoMode : public IMode {};


// sapper modes
//class OnMode : public Mode {};
//class OffMode : public Mode {};

