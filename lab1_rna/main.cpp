#include <iostream>
#include <limits>
#include <string>

#include "rna.h"

using namespace std;


int main() {
	try {
		// something here
	}
	catch (const int& e) {
		if (e == 2) cout << endl << "Wrong RNA array index" << endl;
		else cout << "Some error";
		return -1;
	}
	return 0;
}

