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
	private:
		const size_t &idx;
		RNA& r;
	public:
		nuclRef(const size_t& index, RNA& rna) : idx(index), r(rna) {};
		nuclRef& operator=(Nucl nucl) {
			r.add((Nucl)0, idx, r.rna[idx / r.bitPairsinRnaPart]);
			r.add(nucl, idx, r.rna[idx / r.bitPairsinRnaPart]);
			r.nuclNum -= 2;
			return *this;
		}
		nuclRef& operator=(nuclRef other) {
			Nucl tmp = other.r._getNucl(other.idx);
			r[idx] = tmp;
			return *this;
		}
	};

	char getNucl(const size_t& idx);
	void addNucl(const Nucl& nucl);

	RNA split(const size_t& idx);
	bool isComplementary(RNA& sample);

	void operator=(const RNA& value);
	RNA operator!();
	RNA  operator+(RNA& right);
	bool operator==(const RNA& right);
	bool operator!=(const RNA& right) { return !(*this == right); }
	nuclRef operator[](const size_t &idx);
	friend std::ostream& operator<<(std::ostream& os, RNA r);

	bool isEmpty() { return (rna == nullptr || nuclNum == 0) ? true : false; }
	size_t getNuclNum() { return this->nuclNum; }
	size_t getCapacity() { return this->capacity; }
	size_t getBitPairsinRnaPart() { return this->bitPairsinRnaPart; }
	char getCharValue(const Nucl& nucl);

private:
	size_t nuclNum;
	size_t capacity;
	size_t* rna;
	const size_t bitPairsinRnaPart = (sizeof(size_t) * 4);

	void add(const Nucl& nucl, const size_t& idx, size_t& dst);
	Nucl _getNucl(const size_t& idx);

	// my analog of memcpy because it doesn't work
	void copyMem(size_t* dst, size_t* src, size_t size) {
		size_t* _dst = dst;
		size_t* _src = src;
		for (size_t i = 0; i < size; ++i) {
			*(_dst++) = *(_src++);
		}
	}
	
};

