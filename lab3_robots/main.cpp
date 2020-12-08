#include <iostream>
#include <exception>

#include "Map.h"
#include "View.h"

#include <iostream>
#include <fstream>

using namespace std;

// for debug
void createFile(const size_t& length, const size_t& width, const Object& obj) {
	ofstream out("in.txt");
	if (!out.is_open()) {
		cout << "Все плохо" << endl;
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
		
		// main main
		ConsoleView view;
		Parser parser(new ConsoleInput);
		parser.setMapFileName(argc, argv);
		Manager manager(&parser);
		manager.createExplorer();
		//manager.createSapper();
		view.displayMap(&manager, 21);
		while (1) {
			manager.step();
			view.displayMap(&manager, 21);
		}


	/*
		// debug 
		const Map m("in.txt");
		cout << "Length: " << m.getMapLength() << endl;
		cout << "Width: " << m.getMapWidth() << endl;
		cout << "0,0 object: " << static_cast<char>(m.getObject({ 0, 0 })) << endl;
		for (size_t i = 0; i < m.getMapLength(); ++i) {
			for (size_t j = 0; j < m.getMapWidth(); ++j) {
				cout << static_cast<char>(m.getObject({ i, j }));
			}
			cout << endl;
		}
	*/
	
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

	}
	catch (const exception& e) {
		cout << "Exception: " << e.what() << endl;
		return 0;
	}
	return 0;
}