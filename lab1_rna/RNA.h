#pragma once

#include <iostream>
//using namespace std;


enum Nucl {
	A = 0, // A - 00
	G = 1, // G - 01 
	C = 2, // C - 10
	T = 3 // T - 11 
};


class RNA {
public:
	RNA(const size_t n, const Nucl& nucl);
	RNA(const Nucl& nucl);
	RNA(const RNA& other);
	RNA();
	virtual ~RNA();

	class nuclRef {

	};

	char const getNucl(const size_t& idx);
	void addNucl(const Nucl& nucl);

	RNA split(const size_t& idx);
	bool const isComplementary(RNA& sample);

	void operator=(const RNA& value);
	RNA operator!();
	RNA const operator+(RNA& right);
	bool const operator==(const RNA& right);
	bool const operator!=(const RNA& right) { return !(*this == right); }
	nuclRef operator[](size_t& idx);
	friend std::ostream& operator<<(std::ostream& os, RNA r);

	bool const isEmpty() { return (rna == nullptr || nuclNum == 0) ? true : false; }
	size_t const getNuclNum() { return this->nuclNum; }
	size_t const getCapacity() { return this->capacity; }
	size_t const getBitPairsinRnaPart() { return this->bitPairsinRnaPart; }
	char const getCharValue(const Nucl& nucl);

private:
	size_t nuclNum;
	size_t capacity;
	size_t* rna;
	const size_t bitPairsinRnaPart = (sizeof(size_t) * 4);

	void add(const Nucl& nucl, const size_t& idx, size_t& dst);
	Nucl const _getNucl(const size_t& idx);

	// my analog of memcpy because it doesn't work
	void copyMem(size_t* dst, size_t* src, size_t size) {
		size_t* _dst = dst;
		size_t* _src = src;
		for (size_t i = 0; i < size; ++i) {
			*(_dst++) = *(_src++);
		}
	}
	
};

