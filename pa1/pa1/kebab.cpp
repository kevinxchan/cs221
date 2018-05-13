#include "kebab.h"
#include <string.h>

Kebab::Kebab() {
	// ????
}

bool Kebab::addIngredient(char item) {
	if (this->skewer.size() >= this->maxlength || !this->isValidIngredient(item))
		return false;
	this->skewer.push_back(item);
	return true;
}

void Kebab::buildKebab(std::string s) {
	for (unsigned int i = 0; i < s.length(); i++)
		this->addIngredient(s[i]);
}

unsigned int Kebab::numMeats() const {
	unsigned int ret = 0;
	for (unsigned int i = 0; i < this->skewer.size(); i++) {
		if (this->skewer[i] == 'm' || this->skewer[i] == 'M') 
			ret++;
	}
	return ret;
}

bool Kebab::hasSameIngredients(Kebab& k) const { 
	std::string kAsString = k.listIngredients();
	// hold the number of B, T, M, P, S in this
	unsigned numBInThis = 0;
	unsigned numTInThis = 0;
	unsigned numMInThis = this->numMeats();
	unsigned numPInThis = 0;
	unsigned numSInThis = 0;
	// hold the number of B, T, M, P, S in k
	unsigned numBInK = 0;
	unsigned numTInK = 0;
	unsigned numMInK = k.numMeats();
	unsigned numPInK = 0;
	unsigned numSInK = 0;

	for (unsigned int i = 0; i < this->skewer.size(); i++) {
		if (this->skewer[i] == 'b' || this->skewer[i] == 'B') {
			numBInThis++;
		} else if (this->skewer[i] == 't' || this->skewer[i] == 'T') {
			numTInThis++;
		} else if (this->skewer[i] == 'p' || this->skewer[i] == 'P') {
			numPInThis++;
		} else if (this->skewer[i] == 's' || this->skewer[i] == 'S') {
			numSInThis++;
		} 
	}

	for (char& c : kAsString) {
		if (c == 'b' || c == 'B') {
			numBInK++;
		} else if (c == 't' || c == 'T') {
			numTInK++;
		} else if (c == 'p' || c == 'P') {
			numPInK++;
		} else if (c == 's' || c == 'S') {
			numSInK++;
		}
	}

	return (numBInThis >= numBInK &&
		numTInThis >= numTInK &&
		numMInThis >= numMInK &&
		numPInThis >= numPInK &&
		numSInThis >= numSInK);
}

std::string Kebab::listIngredients() const {
	std::string ret = "";
	for (unsigned int i = 0; i < this->skewer.size(); i++)
		ret += this->skewer[i];
	return ret;
}










