#include "pch.h"

#include <iostream>
#include "../lab1_rna/RNA.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

/*
#include <time.h> // time

#include <stdlib.h>
#include <crtdbg.h>

//using testing::Eq;
//namespace { class RNATest : public testing::Test{ public: }; }

// memory
#define _CRTDBG_MAP_ALLOC
*/

TEST(RnaConstructors, EmptyConstructor) {
	// Arragnge, act
	RNA r;

	// Assert
	EXPECT_EQ(r.getNuclNum(), 0);
	EXPECT_EQ(r.getCapacity(), 0);
	EXPECT_EQ(r.getBitPairsinRnaPart(), (sizeof(size_t) * 8 / 2));
}

TEST(RnaConstructors, SingleNuclConstructor) {
	// Arragnge, act
	RNA a(Nucl::A);
	RNA b(Nucl::C);
	RNA c(Nucl::G);
	RNA d(Nucl::T);

	// Assert
	EXPECT_EQ(Nucl(a[0]), Nucl::A);
	EXPECT_EQ(Nucl(b[0]), Nucl::C);
	EXPECT_EQ(Nucl(c[0]), Nucl::T);
	EXPECT_EQ(Nucl(d[0]), Nucl::G);


	EXPECT_EQ(a.getNuclNum(), 1);
	EXPECT_EQ(b.getNuclNum(), 1);
	EXPECT_EQ(c.getNuclNum(), 1);
	EXPECT_EQ(d.getNuclNum(), 1);

	EXPECT_GT(a.getCapacity(), 0);
	EXPECT_GT(b.getCapacity(), 0);
	EXPECT_GT(c.getCapacity(), 0);
	EXPECT_GT(d.getCapacity(), 0);
}

TEST(RnaConstructors, MultipleNuclConstructor) {
	// Arragnge
	size_t len = 5;

	// Act
	RNA a(len, Nucl::A);
	RNA b(len, Nucl::C);
	RNA c(len, Nucl::G);
	RNA d(len, Nucl::T);
	
	// Assert
	for (size_t i = 0; i < len; ++i) {
		EXPECT_EQ(Nucl(a[i]), Nucl::A);
	}
	for (size_t i = 0; i < len; ++i) {
		EXPECT_EQ(Nucl(b[i]), Nucl::C);
	}
	for (size_t i = 0; i < len; ++i) {
		EXPECT_EQ(Nucl(c[i]), Nucl::G);
	}
	for (size_t i = 0; i < len; ++i) {
		EXPECT_EQ(Nucl(d[i]), Nucl::T);
	}

	EXPECT_EQ(a.getNuclNum(), len);
	EXPECT_EQ(b.getNuclNum(), len);
	EXPECT_EQ(c.getNuclNum(), len);
	EXPECT_EQ(d.getNuclNum(), len);

	EXPECT_EQ(a.getBitPairsinRnaPart(), (sizeof(size_t) * 8 / 2));
	EXPECT_EQ(b.getBitPairsinRnaPart(), (sizeof(size_t) * 8 / 2));
	EXPECT_EQ(c.getBitPairsinRnaPart(), (sizeof(size_t) * 8 / 2));
	EXPECT_EQ(d.getBitPairsinRnaPart(), (sizeof(size_t) * 8 / 2));

	EXPECT_GT(a.getCapacity(), 0);
	EXPECT_GT(b.getCapacity(), 0);
	EXPECT_GT(c.getCapacity(), 0);
	EXPECT_GT(d.getCapacity(), 0);
}

TEST(RnaAdd, AddOneNucl) {
	// Arragnge
	size_t len = 5;
	RNA a;
	RNA b(C);
	RNA c(len, Nucl::G);

	// Act
	a.addNucl(Nucl::C);
	b.addNucl(Nucl::C);
	c.addNucl(Nucl::C);

	// Assert
	EXPECT_EQ(a.getCapacity(), 1);
	EXPECT_EQ(b.getCapacity(), 2);
	EXPECT_EQ(c.getCapacity(), (len + 1));

	EXPECT_EQ(Nucl(a[0]), Nucl::C);
	EXPECT_EQ(Nucl(b[1]), Nucl::C);
	EXPECT_EQ(Nucl(c[len]), Nucl::C);
}

TEST(RnaAdd, AddManyNucls) {
	// Arrange 
	size_t amount = 100;
	RNA a;

	// Act
	for (size_t i = 0; i < amount; ++i) {
		a.addNucl(Nucl(i % 4));
	}

	// Assert 
	for (size_t i = 0; i < amount; ++i) {
		EXPECT_EQ(Nucl(a[i]), Nucl(i % 4));
	}
	EXPECT_EQ(a.getNuclNum(), amount);

}

/*
TEST(RnaAdd, LargeTest) {
	// Arrange 
	RNA r;
	size_t n = 1'000'000;

	// Act
	clock_t tStart = clock();
	for (size_t i = 0; i < n; ++i) {
		r.addNucl(Nucl::G);
	}
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	

	// Assert
	EXPECT_EQ(r.getNuclNum(), n);
	EXPECT_GT((double)(clock() - tStart) / CLOCKS_PER_SEC, 5);
}
*/
/*
TEST(RnaAdd, MemoryLeaks) {
	// Arrange 
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	_CrtMemState _ms;
	_CrtMemCheckpoint(&_ms);

	// Act
	{
		RNA r(100, G);
	}

	_CrtMemDumpAllObjectsSince(&_ms);

	// Assert
	EXPECT_EQ(_ms.lTotalCount, 0); // ?
}
*/

TEST(RnaSplit, Split) {
	// Arragnge
	const size_t n = 10;
	const size_t splitIdx = 7;
	RNA a(n, C);
	RNA b;
	int exception = 0;

	// Act
	try {
		b = a.split(splitIdx);
	}
	catch (int& e) {
		exception = e;
	}

	// Assert
	EXPECT_EQ(a.getNuclNum(), splitIdx);
	EXPECT_EQ(b.getNuclNum(), n - splitIdx);
	
	for (size_t i = 0; i < splitIdx; ++i) {
		EXPECT_EQ(Nucl(a[i]), Nucl::C);
	}
	for (size_t i = 0; i < n-splitIdx; ++i) {
		EXPECT_EQ(Nucl(b[i]), Nucl::C);
	}

	EXPECT_EQ(exception, 0);
}

TEST(RnaSplit, SplitFromZero) {
	// Arragnge
	const size_t n = 10;
	const size_t splitIdx = 0;
	RNA a(n, C);
	RNA b;
	int exception = 0;

	// Act
	try {
		b = a.split(splitIdx);
	}
	catch (int& e) {
		exception = e;
	}

	// Assert
	EXPECT_EQ(a.getNuclNum(), splitIdx);
	EXPECT_EQ(b.getNuclNum(), n);

	for (size_t i = 0; i < n; ++i) {
		EXPECT_EQ(Nucl(b[i]), Nucl::C);
	}
	EXPECT_EQ(exception, 0);
}

TEST(RnaSplit, SplitFromEnd) {
	// Arragnge
	const size_t n = 10;
	const size_t splitIdx = n - 1;
	RNA a(n, C);
	RNA b;
	int exception = 0;

	// Act
	try {
		b = a.split(splitIdx);
	}
	catch (int& e) {
		exception = e;
	}

	// Assert
	EXPECT_EQ(a.getNuclNum(), splitIdx);
	EXPECT_EQ(b.getNuclNum(), n - splitIdx);

	for (size_t i = 0; i < splitIdx; ++i) {
		EXPECT_EQ(Nucl(a[i]), Nucl::C);
	}
	for (size_t i = 0; i < n - splitIdx; ++i) {
		EXPECT_EQ(Nucl(b[i]), Nucl::C);
	}

	EXPECT_EQ(exception, 0);
}

TEST(RnaSplit, SplitEmptyRna) {
	// Arragnge
	RNA a, b;
	int exception = 0;

	// Act
	try {
		a.split(10);
	}
	catch (int& e) {
		exception = e;
	}
	

	// Assert
	EXPECT_EQ(a, b);
	EXPECT_EQ(exception, 2);
}

TEST(RnaSplit, SplitWithWrongIndex) {
	// Arrange
	RNA a(10, G);
	int exception = 0;

	// Act
	try {
		a.split(100);
	}
	catch (int& e) {
		exception = e;
	}

	// Assert
	EXPECT_EQ(exception, 2);
}

TEST(RnaIsComplementary, EmptyRna) {
	// Arragnge
	RNA a, b;

	// Act
	bool resultAB = a.isComplementary(b);
	bool resultBA = b.isComplementary(a);

	// Assert
	EXPECT_EQ(resultAB, true);
	EXPECT_EQ(resultBA, true);
}

TEST(RnaIsComplementary, ComplementaryRna) {
	// Arragnge
	RNA a(A), b(T);
	RNA c(10, C), d(10, G);

	// Act
	bool resultAB = a.isComplementary(b);
	bool resultBA = b.isComplementary(a);

	bool resultCD = c.isComplementary(d);
	bool resultDC = d.isComplementary(c);

	// Assert
	EXPECT_EQ(resultAB, true);
	EXPECT_EQ(resultBA, true);
	EXPECT_EQ(resultCD, true);
	EXPECT_EQ(resultDC, true);
}

TEST(RnaIsComplementary, NotComplementaryRna) {
	// Arragnge
	RNA a(A), b(T), e(G);
	RNA c(10, C), d(10, C);
	RNA g;
	
	// Act
	bool resultAA = a.isComplementary(a);
	bool resultAE = a.isComplementary(e);
	bool resultAC = a.isComplementary(c);
	bool resultCD = c.isComplementary(d);
	bool resultCC = c.isComplementary(c);
	bool resultAG = a.isComplementary(g);
	bool resultGA = g.isComplementary(a);

	// Assert
	EXPECT_EQ(resultAA, false);
	EXPECT_EQ(resultAE, false);
	EXPECT_EQ(resultAC, false);
	EXPECT_EQ(resultCD, false);
	EXPECT_EQ(resultCC, false);
	EXPECT_EQ(resultAG, false);
	EXPECT_EQ(resultGA, false);
}

TEST(RnaOperatorAssign, EmptyRna) {
	// Arragnge
	RNA a, b;

	// Act
	a = b;

	// Assert
	EXPECT_EQ(a.getNuclNum(), 0);
	EXPECT_EQ(a.getCapacity(), 0);
	EXPECT_EQ(b.getNuclNum(), 0);
	EXPECT_EQ(b.getCapacity(), 0);
}

TEST(RnaOperatorAssign, NormalUse) {
	// Arragnge
	RNA a(G), b;
	RNA c(10, T), d(5, G);

	// Act
	b = a;
	d = c;

	// Assert
	EXPECT_EQ(b.getNuclNum(), 1);
	EXPECT_LT(b.getCapacity(), 0);
	EXPECT_EQ(c.getNuclNum(), 10);
	EXPECT_EQ(d.getNuclNum(), 10);
	
	for (size_t i = 0; i < 10; ++i) {
		EXPECT_EQ(Nucl(c[i]), Nucl(d[i]));
	}
}

TEST(RnaOperatorAssign, MakeEmpty) {
	// Arragnge
	RNA a, b(10, C);

	// Act
	b = a;

	// Assert
	EXPECT_EQ(a.getNuclNum(), 0);
	EXPECT_EQ(a.getCapacity(), 0);
	EXPECT_EQ(b.getNuclNum(), 0);
}

TEST(RnaOperatorAssign, AssignToItself) {
	// Arragnge
	RNA a;
	RNA b(T);
	RNA c(10, T);

	// Act
	a = a;
	b = b;
	c = c;

	// Assert
	EXPECT_EQ(a.getNuclNum(), 0);
	EXPECT_EQ(b.getNuclNum(), 1);
	EXPECT_EQ(c.getNuclNum(), 10);
}

TEST(RnaOperatorBuildComplementary, EmptyRna) {
	// Arragnge
	RNA a, b;

	// Act
	b = !a;

	// Assert
	EXPECT_EQ(a.getNuclNum(), 0);
	EXPECT_EQ(b.getNuclNum(), 0);
	EXPECT_EQ(a.getCapacity(), 0);
	EXPECT_EQ(a.getCapacity(), 0);
}

TEST(RnaOperatorBuildComplementary, NormalUse) {
	// Arragnge
	RNA a(10, C), b;

	// Act
	b = !a;

	// Assert
	for (size_t i = 0; i < 10; ++i) {
		EXPECT_EQ(Nucl(b[i]), Nucl::G);
	}
}

TEST(RnaIsComplementary, NormalUse) {
	// Arragnge
	RNA a(10, C), b(10, G);
	RNA c, d;
	RNA e(A), f(T), g(G);

	// Act
	bool result1 = a.isComplementary(b); // 1
	bool result2 = b.isComplementary(a); // 1
	bool result3 = e.isComplementary(f); // 1
	bool result4 = f.isComplementary(e); // 1

	bool result5 = f.isComplementary(g); // 0
	bool result6 = g.isComplementary(f); // 0
	bool result7 = a.isComplementary(g); // 0
	bool result8 = g.isComplementary(a); // 0
	bool result9 = c.isComplementary(d); // 0
	bool result10 = d.isComplementary(c); // 0

	// Assert
	EXPECT_EQ(result1, true);
	EXPECT_EQ(result2, true);
	EXPECT_EQ(result3, true);
	EXPECT_EQ(result4, true);

	EXPECT_EQ(result5, false);
	EXPECT_EQ(result6, false);
	EXPECT_EQ(result7, false);
	EXPECT_EQ(result8, false);
	EXPECT_EQ(result9, false);
	EXPECT_EQ(result10, false);
}

TEST(RnaOperatorEqual, NormalUse) {
	// Arragnge
	RNA a, b;
	RNA c(C), d(C), e(G), f(T), g(A);
	RNA h(10, A), m(2, A), n(10, C);

	// Act
	bool result1 = (a == a); // 1
	bool result2 = (a == b); // 1
	bool result3 = (c == d); // 1
	bool result4 = (c == c); // 1
	bool result5 = (d == e); // 0
	bool result6 = (e == d); // 0
	bool result7 = (f == g); // 0
	bool result8 = (h == h); // 1
	bool result9 = (h == m); // 0
	bool result10 = (h == n); // 0

	// Assert
	EXPECT_EQ(result1, true);
	EXPECT_EQ(result2, true);
	EXPECT_EQ(result3, true);
	EXPECT_EQ(result4, true);
	EXPECT_EQ(result5, false);
	EXPECT_EQ(result6, false);
	EXPECT_EQ(result7, false);
	EXPECT_EQ(result8, true);
	EXPECT_EQ(result9, false);
	EXPECT_EQ(result10, false);
}

TEST(RnaOperatorNotEqual, NormalUse) {
	// Arragnge
	RNA a, b;
	RNA c(C), d(C), e(G), f(T), g(A);
	RNA h(10, A), m(2, A), n(10, C);

	// Act
	bool result1 = (a != a); // 0
	bool result2 = (a != b); // 0
	bool result3 = (c != d); // 0
	bool result4 = (c != c); // 0

	bool result5 = (d != e); // 1
	bool result6 = (e != d); // 1
	bool result7 = (f != g); // 1

	bool result8 = (h != h); // 0

	bool result9 = (h != m); // 1
	bool result10 = (h != n); // 1

	// Assert
	EXPECT_EQ(result1, false);
	EXPECT_EQ(result2, false);
	EXPECT_EQ(result3, false);
	EXPECT_EQ(result4, false);

	EXPECT_EQ(result5, true);
	EXPECT_EQ(result6, true);
	EXPECT_EQ(result7, true);

	EXPECT_EQ(result8, false);

	EXPECT_EQ(result9, true);
	EXPECT_EQ(result10, true);
}

TEST(RnaOperatorGetNuclByIndex, WrongIndex) {
	// Arragnge
	RNA a;
	RNA b(A);
	RNA c(10, G);
	int exception1 = 0;
	int exception2 = 0;
	int exception3 = 0;

	// Act
	try { a[1]; }
	catch (const int& e) { exception1 = e; }

	try { b[100]; }
	catch (const int& e) { exception2 = e; }

	try { c[100]; }
	catch (const int& e) { exception3 = e; }

	// Assert
	EXPECT_EQ(exception1, 2);
	EXPECT_EQ(exception2, 2);
	EXPECT_EQ(exception3, 2);
}

TEST(RnaOperatorGetNuclByIndex, NormalUse) {
	// Arragnge
	size_t size = 10;
	RNA a(size, A), b(size, C), c(size, G), d(size, T);
	Nucl* result1 = new Nucl[size];
	Nucl* result2 = new Nucl[size];
	Nucl* result3 = new Nucl[size];
	Nucl* result4 = new Nucl[size];

	// Act
	for (size_t i = 0; i < size; ++i) {
		result1[i] = Nucl(a[i]);
	}
	for (size_t i = 0; i < size; ++i) {
		result2[i] = Nucl(b[i]);
	}
	for (size_t i = 0; i < size; ++i) {
		result3[i] = Nucl(c[i]);
	}
	for (size_t i = 0; i < size; ++i) {
		result4[i] = Nucl(d[i]);
	}

	// Assert
	for (size_t i = 0; i < size; ++i) {
		EXPECT_EQ(result1[i], Nucl::A);
	}
	for (size_t i = 0; i < size; ++i) {
		EXPECT_EQ(result2[i], Nucl::C);
	}
	for (size_t i = 0; i < size; ++i) {
		EXPECT_EQ(result3[i], Nucl::G);
	}
	for (size_t i = 0; i < size; ++i) {
		EXPECT_EQ(result4[i], Nucl::T);
	}

	delete[] result1;
	delete[] result2;
	delete[] result3;
	delete[] result4;
}

TEST(RnaOperatorGetNuclByIndex, ConstRna) {
	// Arragnge
	const RNA a(10, C);
	RNA b(10, G);
	Nucl result1; 
	Nucl result2;

	// Act
	result1 = Nucl(a[1]);
	
	b[5] = a[1];
	result2 = Nucl(b[5]);

	// Assert
	EXPECT_EQ(result1, Nucl::C);
	EXPECT_EQ(result2, Nucl::C);
}

TEST(RnaIsEmpty, NormalUse) {
	// Arragnge
	RNA a;
	const RNA b;
	RNA c(T), d(10, G);
	const RNA e(A);
	
	// Act
	bool result1 = a.isEmpty(); // 1
	bool result2 = b.isEmpty(); // 1

	bool result3 = c.isEmpty(); // 0
	bool result4 = d.isEmpty(); // 0
	bool result5 = e.isEmpty(); // 0

	// Assert
	EXPECT_EQ(result1, true);
	EXPECT_EQ(result2, true);

	EXPECT_EQ(result3, false);
	EXPECT_EQ(result4, false);
	EXPECT_EQ(result5, false);
}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}