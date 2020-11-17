
#include <iostream>
#include <exception>
#include "Map.h"

using namespace std;

int main(int argc, char* argv[]) {
	/*
	Map m;

	for (size_t i = 0; i < 30; ++i) {
		for (size_t j = 0; j < 30; ++j) {
			std::cout << char(m.getMap()[i][j]) << ' ';
		}
		std::cout << std::endl;
	}
	*/
	try {
		//if (argc != 1) throw std::exception("Incorrect number of arguements");
		// else send filename to parser


	}
	catch (std::exception& e) {
		std::cout << "Some problems: " << e.what() << std::endl;
	}

	return 0;
}