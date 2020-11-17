#pragma once

class Command {
public:
	enum class Direction {
		up, down, left, right
	};
	enum class ExplorerMode {
		manual, automatical, scan
	};
	enum class SapeerMode {
		on, off
	};
protected:


};

class ChangeExplorerMode : public Command {
public:

private:

};

class ChangeSapperMode : public Command {
public:

private:

};

class ExplorerCommand : public Command {
public:

private:

};

