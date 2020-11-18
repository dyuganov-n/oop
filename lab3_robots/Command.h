#pragma once

#include <string>
using namespace std;

class Command {
public:	
	void virtual setCommand(const string& cmd) = 0;
	//string virtual getCommand() = 0;
};

class ChangeModeCommand : public Command {
public:
	void setCommand(const string& cmd);

};

class ManualModeCommand : public Command {
public:
	// interface
	void setCommand(const string& cmd);

	// other
	enum class Direction { up, down, left, right };
	void virtual grab() = 0;
	void virtual move(const Direction& dir) = 0;
	void virtual scan() = 0;
};

class MoveManualCommand : public ManualModeCommand {
public:


private:

};

class GrabManualCommand : public ManualModeCommand {
public:

private:

};

class ScanManualCommand : public ManualModeCommand {
public:

private:

};

