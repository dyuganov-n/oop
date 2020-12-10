#pragma once

#include "Command.h"

class CommandHandler
{
public:
	CommandHandler() = default;
	void HandleCommand(ICommand* command) {
		if (dynamic_cast<ChangeModeCommand*>(command)) {
			command->execute();
		}
		else {
			// what else?
		}
	}
};

