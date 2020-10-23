#include "RNA.h"

#include <iostream>

using namespace std;

RNA::RNA(const size_t num, const Nucl& nucl) {
	this->capacity = 0;
	this->nuclNum = 0;
	this->rna = nullptr;
	for (size_t i = 0; i < num; i++) {
		addNucl(nucl);
	}
}

RNA::RNA(const Nucl& nucl) {
	this->capacity = 0;
	this->nuclNum = 0;
	this->rna = nullptr;
	addNucl(nucl);
}

RNA::RNA(const RNA &other) {
	this->nuclNum = other.nuclNum;
	this->capacity = other.capacity;
	this->rna = nullptr;

	if (other.rna != nullptr) {
		const size_t rnaSize = capacity / bitPairsinRnaPart;
		this->rna = new size_t[rnaSize];
		copyMem(this->rna, other.rna, rnaSize);
	}
}

RNA::RNA(){
	this->capacity = 0;
	this->nuclNum = 0;
	this->rna = nullptr;
}

RNA::~RNA() {
	delete[] this->rna;
	rna = nullptr;
}

void RNA::add(const Nucl &nucl, const size_t& idx, size_t& dst) {
	size_t tmp = (size_t)nucl;

	tmp <<= 2 * (bitPairsinRnaPart - 1 - idx); // ...00 ?? 00 ...
	dst |= tmp;

	++nuclNum;
}

void RNA::addNucl(const Nucl& nucl) {

	size_t rnaArrayIdx = nuclNum / bitPairsinRnaPart;
	size_t rnaPartIdx = nuclNum % bitPairsinRnaPart;

	// First element 
	if (nuclNum == 0 && capacity == 0) {
		rna = new size_t[1];
		rna[0] = 0;
		capacity = bitPairsinRnaPart; // capacity += bitPairsInRnaPart;
		add(nucl, 0, rna[0]);
	}
	// Not first element, but need extra space
	else if (nuclNum == capacity) {
		const size_t newMemSize = 2 * (nuclNum / bitPairsinRnaPart);
		size_t* tmp = new size_t[newMemSize];
		for (size_t i = 0; i < newMemSize; ++i) {
			tmp[i] = 0;
		}
	
		size_t* tmp1 = tmp;
		size_t* rna1 = rna;
		for (size_t i = 0; i < newMemSize / 2; ++i) { 
			*(tmp1++) = *(rna1++);
		}

		delete[] rna;
		rna = tmp;

		capacity = newMemSize * bitPairsinRnaPart;
		add(nucl, 0, rna[rnaArrayIdx]);
	}
	// Just insert
	else {
		add(nucl, rnaPartIdx, rna[rnaArrayIdx]);
	}
}

Nucl RNA::_getNucl(const size_t& idx) {
	
	size_t rnaPartIdx = idx / bitPairsinRnaPart;
	size_t localIdxInRnaPart = ((bitPairsinRnaPart) - (idx % (bitPairsinRnaPart)) - 1);
	size_t rnaPart = rna[rnaPartIdx];
	size_t nucl = (size_t)3; // ... 00 00 11
	
	nucl <<= localIdxInRnaPart*2;
	nucl &= rnaPart;
	nucl >>= localIdxInRnaPart*2;

	return (Nucl)nucl;
}

// does not work with const RNA&
char RNA::getNucl(const size_t& idx) {
	if (idx > nuclNum - 1 || rna == nullptr) return 'E';
	return getCharValue(_getNucl(idx));
}

char RNA::getCharValue(const Nucl& nucl) {
	switch (nucl) {
	case Nucl::A:
		return 'A';
	case Nucl::C:
		return 'C';
	case Nucl::G:
		return 'G';
	case Nucl::T:
		return 'T';
	}
	return 'E';
}

RNA RNA::split(const size_t& idx) {
	
	RNA result;
	if (idx > nuclNum) return result;

	size_t resultNuclNum = this->nuclNum - idx;
	for (size_t i = 0; i < resultNuclNum; ++i) {
		result.addNucl(this->_getNucl(i+idx));
	}

	RNA tmp;
	for (size_t i = 0; i < idx; ++i) {
		tmp.addNucl(this->_getNucl(i));
	}

	*this = tmp;
		
	return result;
}

RNA RNA::operator!() {
	if (nuclNum == 0) return *this;

	RNA result(*this);
	
	size_t rnaArrSize = (nuclNum / bitPairsinRnaPart);
	for (size_t i = 0; i <= rnaArrSize; ++i) {
		result.rna[i] = ~result.rna[i];
	}

	// if the end is not full, need set it with 0..
	size_t notUsedBitsOfRnaPart = 2*(bitPairsinRnaPart - (nuclNum % bitPairsinRnaPart));
	result.rna[rnaArrSize] >>= notUsedBitsOfRnaPart;
	result.rna[rnaArrSize] <<= notUsedBitsOfRnaPart;

	return result;
}

bool RNA::isComplementary(RNA& sample) {
	if(this->rna == nullptr || sample.rna == nullptr) return false;
	
	RNA complementary = !sample;
	if (complementary == *this) return true;
	else return false;
}

RNA RNA::operator+(RNA& right){
	
	RNA result(*this);
	if (this->nuclNum == 0 && right.nuclNum == 0) return result;
	
	size_t thisMemSize = this->capacity / this->bitPairsinRnaPart;
	size_t resultNuclNum = this->nuclNum + right.nuclNum;

	for (size_t i = 0; i < right.nuclNum; ++i) {
		result.addNucl(right._getNucl(i));
	}

	return result;
}

bool RNA::operator==(const RNA& right){
	if (this->nuclNum != right.nuclNum) return false;
	for (size_t i = 0; i < this->capacity / this->bitPairsinRnaPart; ++i) {
		if (this->rna[i] != right.rna[i]) return false;
	}
	return true;
}

void RNA::operator=(const RNA& value) {
	this->nuclNum = value.nuclNum;
	this->capacity = value.capacity;

	delete[] this->rna;
	this->rna = nullptr;

	size_t newMemSize = capacity / bitPairsinRnaPart;
	if (newMemSize > 0) {
		this->rna = new size_t[newMemSize];
		copyMem(this->rna, value.rna, newMemSize);
	}
}

ostream& operator<<(ostream& os, RNA r) {
	for (size_t i = 0; i < r.getNuclNum(); ++i) {
		os << r.getNucl(i) << endl;
	}
	return os;
}

RNA::nuclRef RNA::operator[](const size_t &idx){
	return RNA::nuclRef(idx, *this);
}