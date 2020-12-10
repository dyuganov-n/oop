#pragma once

//#include "Map.h"
//#include "Robot.h"

#include "Sapper.h"
#include "Explorer.h"
#include "Manager.h"

#include <iostream>
#include <exception>

//using namespace std;

// апрашивает у менеджера карту с роботами
class IView {
public:
	virtual void displayMap(Manager* mngr, const int& oneSideViewField) = 0;
};

class ConsoleView : public IView {
public:
	void displayMap(Manager* mngr, const int& oneSideViewField);

private:
	bool robotInCell(vector<pair<IMode*, IRobot*>>& robots, ptrdiff_t x, ptrdiff_t y);
};

