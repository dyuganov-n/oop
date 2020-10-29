#pragma once

#include <iostream>

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

	class constNuclRef {
	private:
		const size_t& idx;
		const RNA& r;
	public:
		constNuclRef(const size_t& index, const RNA& rna) : idx(index), r(rna) {};
		const size_t& getIndex() const { return this->idx; }
		const RNA& getRna() const { return this->r; }
		operator Nucl() const { return r._getNucl(idx); }
	};
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
		nuclRef& operator=(nuclRef& other) {
			Nucl tmp = other.r._getNucl(other.idx);
			r[idx] = tmp;
			return *this;
		}
		nuclRef& operator=(const constNuclRef& other) {
			Nucl nucl = other.getRna()._getNucl(other.getIndex());
			r.add((Nucl)0, idx, r.rna[idx / r.bitPairsinRnaPart]);
			r.add(nucl, idx, r.rna[idx / r.bitPairsinRnaPart]);
			r.nuclNum -= 2;
			return *this;
		}
		operator Nucl() const { return r._getNucl(idx); }
	};

	void addNucl(const Nucl& nucl);

	RNA split(const size_t& idx);
	bool isComplementary(const RNA& sample) const;

	RNA operator=(const RNA& value);
	RNA operator!() const;
	RNA operator+(const RNA& right) const;
	bool operator==(const RNA& right) const;
	bool operator!=(const RNA& right) const { return !(*this == right); }
	nuclRef operator[](const size_t &idx);
	constNuclRef operator[](const size_t& idx) const;

	friend std::ostream& operator<<(std::ostream& os, RNA r);

	bool isEmpty() const { return (rna == nullptr || nuclNum == 0) ? true : false; }
	size_t getNuclNum() const { return this->nuclNum; }
	size_t getCapacity() const { return this->capacity; }
	size_t getBitPairsinRnaPart() const { return this->bitPairsinRnaPart; }

private:
	size_t nuclNum;
	size_t capacity;
	size_t* rna;
	const size_t bitPairsinRnaPart = (sizeof(size_t) * 4);

	void add(const Nucl& nucl, const size_t& idx, size_t& dst);
	Nucl _getNucl(const size_t& idx) const;

	char getCharValue(const Nucl& nucl) const;
	char getNucl(const size_t& idx) const;

	// my analog of memcpy because it doesn't work
	void copyMem(size_t* dst, size_t* src, size_t size) {
		size_t* _dst = dst;
		size_t* _src = src;
		for (size_t i = 0; i < size; ++i) {
			*(_dst++) = *(_src++);
		}
	}
	
};

