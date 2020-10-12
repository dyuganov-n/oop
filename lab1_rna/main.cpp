#include <iostream>
#include <limits>

#include "rna.h"

using namespace std;

int main() {
	cout << sizeof(size_t) << endl << endl;

	RNA a(10, Nucl::C);

	for (int i = 0; i < 12; ++i) {
		cout << a.getNucl(i) << endl;
	}

	cout << endl << "add and print" << endl;

	a.addNucl(Nucl::A);
	a.addNucl(Nucl::C);
	a.addNucl(Nucl::T);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::A);
	a.addNucl(Nucl::C); 
	a.addNucl(Nucl::T);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::A);
	a.addNucl(Nucl::C);
	a.addNucl(Nucl::T);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::G);
	a.addNucl(Nucl::G);

	for (size_t i = 0; i < 45; ++i) {
		cout << i << ' ' << a.getNucl(i) << endl;
	}

	a.buildComplimentaryRna();

	return 0;
}