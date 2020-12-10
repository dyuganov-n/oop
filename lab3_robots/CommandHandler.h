#pragma once

#include "Command.h"

class CommandHandler
{
public:
	CommandHandler() = default;
	void HandleCommand(ICommand* command) {
		command->execute();
	}
};

