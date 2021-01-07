#pragma once

#include "Manager.h"

#include <iostream>
#include <exception>

// запрашивает у менеджера карту с роботами
enum class ViewMode { GlobalMap, LocalMap };
class IView {
public:
	virtual void displayMap(Manager* mngr, const int& oneSideViewField, const ViewMode& VMode) = 0;
};

class ConsoleView : public IView {
public:
	void displayMap(Manager* mngr, const int& oneSideViewField, const ViewMode& VMode);

private:
	bool robotInCell(vector<pair<IMode*, IRobot*>>& robots, const Coordinates& coords);
};

