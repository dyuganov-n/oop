#include <iostream>
#include <exception>

#include "Map.h"
#include "View.h"

using namespace std;

int main(int argc, char* argv[]) {
	try {
		Parser parser(new ConsoleInput);
		parser.setMapFileName(argc, argv);
		Manager manager(&parser);
		manager.createExplorer();
		manager.createSapper();
		while (1) {
			manager.step();
		}

	}
	catch (std::exception& e) {
		std::cout << "Some problems: " << e.what() << std::endl;
	}

	return 0;
}