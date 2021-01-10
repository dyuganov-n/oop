#include <iostream>

using namespace std;

#include "tuple_print.h"
#include <tuple>

int main() {

	tuple<int, double, size_t, string> a = { -1, 1.11, 11, "azaza" };
	cout << a << endl;

	return 0;
}