#include <iostream>
#include <limits>
#include <string>

#include "rna.h"

#include <time.h> // time

// memory
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;


int main() {

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	_CrtMemState _ms;
	_CrtMemCheckpoint(&_ms);

	try {
		_CrtDumpMemoryLeaks();
		{
			// 1'000'000 nucls test
			RNA r;
			clock_t tStart = clock();
			for (size_t i = 0; i < 1'000'000; ++i) {
				r.addNucl(Nucl::G);
			}
			printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
			cout << endl;
		}

	}
	catch (const int& e) {
		if (e == 2) cout << endl << "Wrong RNA array index" << endl;
		else cout << "Some error";
		return -1;
	}

	_CrtMemDumpAllObjectsSince(&_ms);

	return 0;
}

