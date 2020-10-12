#pragma once

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
	~RNA();

	char const getNucl(size_t idx);
	void addNucl(const Nucl& nucl);

	void trim(const size_t idx);
	RNA buildComplimentaryRna(const RNA& source);
	RNA split(const size_t& idx);
	bool isComplementary(RNA& sample);

	size_t const getNuclNum(){ return this->nuclNum; }
	size_t const getCapacity() { return this->capacity; }
	size_t const getBitPairsinRnaPart() { return this->bitPairsinRnaPart; }

private:
	size_t nuclNum;
	size_t capacity;
	size_t* rna;
	const size_t bitPairsinRnaPart = (sizeof(size_t) * 4);

	void add(const Nucl& nucl, const size_t& idx, size_t& dst);
	char const getCharValue(const Nucl& nucl);
};

