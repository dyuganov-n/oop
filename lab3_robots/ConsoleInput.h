#pragma once

#include <iostream>
#include <string>
using std::cin;
using std::string;

#include <algorithm>
#include <cctype>
//using namespace std;

class ConsoleInput {
public:
	string getString() {
		string str;
		cin >> str;
		//std::transform(str.begin(), str.end(), str.begin(), tolower);
		return str;
	}
	size_t getNumber() {
		size_t n;
		cin >> n;
		return n;
	}
};

