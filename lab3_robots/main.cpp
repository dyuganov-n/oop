#include <iostream>
#include <exception>

#include "Map.h"
#include "View.h"
#include "Parser.h"
#include "CommandHandler.h"

#include <iostream>
#include <fstream>

using namespace std;

// for debug
void createFile(const size_t& length, const size_t& width, const Object& obj) {
	ofstream out("in.txt");
	if (!out.is_open()) {
		cout << "Can't create file" << endl;
	}
	for (size_t i = 0; i < length; ++i) {
		for (size_t j = 0; j < width; ++j) {
			out << static_cast<char>(obj);
		}
		out << endl;
	}
	out.close();
}

int main(int argc, char* argv[]) {
	try {
		
		ConsoleView view;
		const size_t cellsInView = 11;

		CommandHandler comHandler;
		Parser parser(new ConsoleInput);
		parser.setMapFileName(argc, argv);

		Manager manager(parser.getMapFileName());
		manager.CreateExplorer();
		//manager.CreateSapper(); // no empty space because Explorers map is nor discovered at all
		view.displayMap(&manager, cellsInView, ViewMode::LocalMap);

		if (manager.EnvironmentPtrIsNull()) {
			throw exception("Manager can't make step. Environment pointer is nullptr.");
			return 0;
		}
		else if (manager.RepeaterPtrIsNull()) {
			throw exception("Manager can't make step. Repeater pointers is nullptr.");
			return 0;
		}
		while (1) {
			ICommand* command = parser.parseCommand(&manager);
			comHandler.HandleCommand(command);
			delete command;
			view.displayMap(&manager, cellsInView, ViewMode::LocalMap);
			//view.displayMap(&manager, cellsInView, ViewMode::GlobalMap);
		}

		//createFile(1010, 1100, Object::empty);

	}
	catch (const exception& e) {
		cout << "Exception: " << e.what() << endl;
		return 0;
	}

	return 0;
}