#include <iostream>
#include <exception>

#include "Map.h"
#include "View.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
	
	try {
		ConsoleView view;
		Parser parser(new ConsoleInput);
		parser.setMapFileName(argc, argv);
		Manager manager(&parser);
		//manager.createExplorer();
		//manager.createSapper();
		//view.showMap(&manager, 21);
		while (1) {
			manager.step();
			view.showMap(&manager, 21);
		}
	}
	catch (std::exception& e) {
		std::cout << "Some problems: " << e.what() << std::endl;
	}
	
	/*
	// create file
	ofstream out("in.txt");
	if (!out.is_open()) {
		cout << "Все плохо" << endl;
		return 0;
	}
	for (size_t i = 0; i < 1100; ++i) {
		for (size_t j = 0; j < 1000; ++j) {
			out << static_cast<char>(Object::empty);
		}
		out << endl;
	}
	out.close();
	*/
	return 0;
}