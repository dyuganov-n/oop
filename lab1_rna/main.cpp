#include <iostream>
#include <limits>
#include <string>

#include "rna.h"

#include <time.h>

using namespace std;


int main() {
	try {


		// 1'000'000 nucls test
		RNA r; 
		clock_t tStart = clock();
		for (size_t i = 0; i < 1'000'000; ++i) {
			r.addNucl(Nucl::G);
		}
		printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
		
	}
	catch (const int& e) {
		if (e == 2) cout << endl << "Wrong RNA array index" << endl;
		else cout << "Some error";
		return -1;
	}
	return 0;
}

// TODO
	// tests for every method
	// memory leak check
	// 1'000'000 time test