#pragma once

class Mode {

public:
	void virtual setMode() = 0;
	void virtual setCommand() = 0;
};

//explorer modes
class ManualMode : public Mode {};
class ScanMode : public Mode {};
class AutoMode : public Mode {};

// sapper modes
//class OnMode : public Mode {};

//class OffMode : public Mode {};

