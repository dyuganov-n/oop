#include <iostream>
#include <fstream>
#include <exception>

using namespace std;

#include "CSVParser.h"
#include "tuple_print.h"


int main() {
	try {
		ifstream file("test1.csv");
		if (!file.is_open()) {
			throw exception("Input file was not opened.");
			return 0;
		}

		//CSVParser<string, char, double, int> parser(file, 0);
		CSVParser<int, string, string, double, char> parser(file, 0);
		//CSVParser<int, string> parser(file, 0 /*skip first lines count*/);
		parser.setSepSymbol('/');
		for (auto& rs : parser) {
			cout << rs << endl;
		}


		file.close();
		return 0;
	}
	catch (const exception& e) {
		cout << "Exception: " << e.what() << endl;
		return 0;
	}
}