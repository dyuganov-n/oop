#include "pch.h"

#include <iostream>
#include "../lab1_rna/RNA.h"

#include <gtest/gtest.h>

/*
#include <time.h> // time

#include <stdlib.h>
#include <crtdbg.h>

//using testing::Eq;
//namespace { class RNATest : public testing::Test{ public: }; }

// memory
#define _CRTDBG_MAP_ALLOC
*/

TEST(Constructors, EmptyConstructor) {
	// Arragnge, act
	RNA r;

	// Assert
	EXPECT_EQ(r.getNuclNum(), 0);
	EXPECT_EQ(r.getCapacity(), 0);
	EXPECT_EQ(r.getBitPairsinRnaPart(), (sizeof(size_t) * 8 / 2));
}

TEST(Constructors, SingleNuclConstructor) {
	// Arragnge, act
	RNA a(Nucl::A);
	RNA b(Nucl::C);
	RNA c(Nucl::G);
	RNA d(Nucl::T);

	// Assert
	EXPECT_EQ(Nucl(a[0]), Nucl::A);
	EXPECT_EQ(Nucl(b[0]), Nucl::C);
	EXPECT_EQ(Nucl(c[0]), Nucl::G);
	EXPECT_EQ(Nucl(d[0]), Nucl::T);


	EXPECT_EQ(a.getNuclNum(), 1);
	EXPECT_EQ(b.getNuclNum(), 1);
	EXPECT_EQ(c.getNuclNum(), 1);
	EXPECT_EQ(d.getNuclNum(), 1);

	EXPECT_GT(a.getCapacity(), 0);
	EXPECT_GT(b.getCapacity(), 0);
	EXPECT_GT(c.getCapacity(), 0);
	EXPECT_GT(d.getCapacity(), 0);
}

TEST(Constructors, MultipleNuclConstructor) {
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

TEST(Add, AddOneNucl) {
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
	EXPECT_EQ(a.getNuclNum(), 1);
	EXPECT_EQ(b.getNuclNum(), 2);
	EXPECT_EQ(c.getNuclNum(), (len + 1));

	EXPECT_EQ(Nucl(a[0]), Nucl::C);
	EXPECT_EQ(Nucl(b[1]), Nucl::C);
	EXPECT_EQ(Nucl(c[len]), Nucl::C);
}

TEST(Add, AddManyNucls) {
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

TEST(Split, Split) {
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
	for (size_t i = 0; i < n - splitIdx; ++i) {
		EXPECT_EQ(Nucl(b[i]), Nucl::C);
	}

	EXPECT_EQ(exception, 0);
}

TEST(Split, SplitFromZero) {
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

TEST(Split, SplitFromEnd) {
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

TEST(Split, SplitEmptyRna) {
	// Arragnge
	RNA a, b;

	// Act
	// Assert
	ASSERT_THROW(a.split(10), std::exception);
	EXPECT_EQ(a, b);
}

TEST(Split, SplitWithWrongIndex) {
	// Arrange
	RNA a(10, G);

	// Act
	// Assert
	ASSERT_THROW(a.split(100), std::exception);
}

TEST(IsComplementary, EmptyRna) {
	// Arragnge
	RNA a, b;

	// Act
	bool resultAB = a.isComplementary(b);
	bool resultBA = b.isComplementary(a);

	// Assert
	EXPECT_EQ(resultAB, false);
	EXPECT_EQ(resultBA, false);
}

TEST(IsComplementary, ComplementaryRna) {
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

TEST(IsComplementary, NotComplementaryRna) {
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

TEST(OperatorAssign, EmptyRna) {
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

TEST(OperatorAssign, NormalUse) {
	// Arragnge
	RNA a(G), b;
	RNA c(10, T), d(5, G);

	// Act
	b = a;
	d = c;

	// Assert
	EXPECT_EQ(b.getNuclNum(), 1);
	EXPECT_GT(b.getCapacity(), 0);
	EXPECT_EQ(c.getNuclNum(), 10);
	EXPECT_EQ(d.getNuclNum(), 10);

	for (size_t i = 0; i < 10; ++i) {
		EXPECT_EQ(Nucl(c[i]), Nucl(d[i]));
	}
}

TEST(OperatorAssign, MakeEmpty) {
	// Arragnge
	RNA a, b(10, C);

	// Act
	b = a;

	// Assert
	EXPECT_EQ(a.getNuclNum(), 0);
	EXPECT_EQ(a.getCapacity(), 0);
	EXPECT_EQ(b.getNuclNum(), 0);
}

TEST(OperatorAssign, AssignToItself) {
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

TEST(OperatorBuildComplementary, EmptyRna) {
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

TEST(OperatorBuildComplementary, NormalUse) {
	// Arragnge
	RNA a(10, C), b;

	// Act
	b = !a;

	// Assert
	for (size_t i = 0; i < 10; ++i) {
		EXPECT_EQ(Nucl(b[i]), Nucl::G);
	}
}

TEST(IsComplementary, NormalUse) {
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

TEST(OperatorEqual, NormalUse) {
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

TEST(OperatorNotEqual, NormalUse) {
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

TEST(OperatorGetNuclByIndex, WrongIndex) {
	// Arragnge
	RNA a;
	RNA b(A);
	RNA c(10, G);
	const RNA d;
	const RNA e(A);
	const RNA f(10, G);

	// Act
	// Assert
	ASSERT_THROW(a[100], std::exception);
	ASSERT_THROW(b[100], std::exception);
	ASSERT_THROW(c[100], std::exception);
	ASSERT_THROW(d[100], std::exception);
	ASSERT_THROW(e[100], std::exception);
	ASSERT_THROW(f[100], std::exception);

}

TEST(OperatorGetNuclByIndex, NormalUse) {
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

TEST(OperatorGetNuclByIndex, ConstRna) {
	// Arragnge
	const RNA a(10, C);
	RNA b(10, G);

	// Act
	Nucl result1 = Nucl(a[1]);

	b[5] = a[1];
	Nucl result2 = Nucl(b[5]);

	// Assert
	EXPECT_EQ(result1, Nucl::C);
	EXPECT_EQ(result2, Nucl::C);
}

TEST(IsEmpty, NormalUse) {
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
