#pragma once

#include <iostream>
#include <string>
using std::cin;
using std::string;

class ConsoleInput {
public:
	const string& getString() {
		string c;
		cin >> c;
		return c;
	}
	const size_t& getNumber() {
		size_t n;
		cin >> n;
		return n;
	}
};

