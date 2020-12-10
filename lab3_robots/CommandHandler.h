#pragma once

#include "Command.h"

class CommandHandler {
public:
	CommandHandler() = default;
	void HandleCommand(ICommand* command) {
		if (command == nullptr) {
			throw exception("Command handler error. Command is nullptr.");
		}
		else {
			command->execute();
		}
		//if (dynamic_cast<ChangeModeCommand*>(command)) { command->execute(); }

	}
};

