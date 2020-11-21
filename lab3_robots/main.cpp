#include <iostream>
#include <exception>

#include "Map.h"
#include "View.h"



using namespace std;

int main(int argc, char* argv[]) {
	try {

	}
	catch (std::exception& e) {
		std::cout << "Some problems: " << e.what() << std::endl;
	}

	return 0;
}