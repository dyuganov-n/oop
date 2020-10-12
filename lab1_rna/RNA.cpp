#include "RNA.h"

#include <iostream>
#include <cstring> // memcpy()

using namespace std;

// adds num nucls nucl
RNA::RNA(const size_t num, const Nucl& nucl) {
	this->capacity = 0;
	this->nuclNum = 0;
	this->rna = nullptr;
	for (size_t i = 0; i < num; i++) {
		addNucl(nucl);
	}
}

// adds 1 nucl
RNA::RNA(const Nucl& nucl) {
	this->capacity = 0;
	this->nuclNum = 0;
	this->rna = nullptr;
	addNucl(nucl);
}

// copy constructor
RNA::RNA(const RNA &other) {
	this->nuclNum = other.nuclNum;
	this->capacity = other.capacity;
	this->rna = nullptr;

	const size_t rnaSize = capacity / bitPairsinRnaPart;
	this->rna = new size_t[rnaSize];
	memcpy(this->rna, other.rna, rnaSize);
}

// empty constructor
RNA::RNA(){
	this->capacity = 0;
	this->nuclNum = 0;
	this->rna = nullptr;
}

// destructor
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
	
		//memcpy(tmp, rna, nuclNum*4); // doesn't work (don't know why)
		//for (size_t i = 0; i < newMemSize / 2; ++i) {tmp[i] = rna[i];} // not effective
		size_t* tmp1 = tmp;
		size_t* rna1 = rna;
		for (size_t i = 0; i < newMemSize / 2; ++i) { 
			*(tmp1++) = *(rna1++);
		}
		delete[] rna;
		rna = tmp;

		capacity = newMemSize * bitPairsinRnaPart;

		size_t rnaArrayIdx = nuclNum / bitPairsinRnaPart;
		add(nucl, 0, rna[rnaArrayIdx]);
	}
	// Just insert
	else {
		size_t rnaArrayIdx = nuclNum / bitPairsinRnaPart;
		size_t rnaPartIdx = nuclNum % bitPairsinRnaPart;
		add(nucl, rnaPartIdx, rna[rnaArrayIdx]);
	}
}

char const RNA::getNucl(size_t idx) {
	// correct input check
	if (idx > nuclNum - 1 || rna == nullptr) return 'E';

	size_t rnaPartIdx = idx / bitPairsinRnaPart;
	size_t localIdxInRnaPart = ((bitPairsinRnaPart) - (idx % (bitPairsinRnaPart)) - 1);
	size_t rnaPart = rna[rnaPartIdx];
	size_t nucl = (size_t)3; // ... 00 00 11
	
	nucl <<= localIdxInRnaPart*2;
	nucl &= rnaPart;
	nucl >>= localIdxInRnaPart*2;

	return getCharValue((Nucl)nucl);
}

char const RNA::getCharValue(const Nucl& nucl) {
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

// WIP
void RNA::trim(const size_t idx) {
	if (idx > nuclNum) return;
	
	size_t newNuclNum = idx + 1;
	const size_t newMemSize = (newNuclNum / bitPairsinRnaPart) + 1;
	capacity = newMemSize * bitPairsinRnaPart;

	size_t* tmp = new size_t[newMemSize];
	for (size_t i = 0; i < newMemSize; ++i) {
		tmp[i] = 0;
	}
	memcpy(tmp, rna, newMemSize);
	// удалить еще несколько нуклеотидов с конца, чтобы их было idx+1
	
	delete[] rna;
	rna = nullptr;
	rna = tmp;
	
	nuclNum = newNuclNum;
}

// WIP
RNA RNA::buildComplimentaryRna(const RNA& source) {
	RNA result = RNA(source);
	size_t rnaArrSize = nuclNum / bitPairsinRnaPart;

	for (size_t i = 0; i < rnaArrSize; ++i) {
		result.rna[i] = !result.rna[i];
	}
	// еще если конец не полный, то происходит ЖОПА (нужно аккуратно занулить)
	result.rna[rnaArrSize] <<= bitPairsinRnaPart - (nuclNum % bitPairsinRnaPart);
	result.rna[rnaArrSize] >>= bitPairsinRnaPart - (nuclNum % bitPairsinRnaPart);
	// test this
	return result;
}

// WIP
RNA RNA::split(const size_t& idx)
{
	return RNA();
}

// NEED TESTS
bool RNA::isComplementary(RNA& sample){
	if (this->rna == nullptr || sample.rna == nullptr) return false;
	for (size_t i = 0; i < nuclNum / bitPairsinRnaPart; ++i) {
		if (this->rna[i] != sample.rna[i]) return false;
	}
	return true;
}



