#include "grill.h"

Grill::Grill() {
	
}

bool Grill::swap(unsigned int pos1, unsigned int pos2) {
	// convert from 1-indexed to 0-indexed
	unsigned int index1 = pos1 - 1;
	unsigned int index2 = pos2 - 1;

	// checks for invalid positions
	if (index1 >= this->rack.size() || index2 >= this->rack.size())
		return false;
	// check for swap in the same position
	if (index1 == index2)
		return true;
	// ensures only one case dealt with (swaps are same)
	if (index1 > index2) {
		unsigned int temp = index1;
		index1 = index2;
		index2 = temp;
	}

	// initialize kebabs in pos1 and pos2
	Kebab* p1;
	Kebab* p2; 

	for (unsigned int i = 0; i < this->rack.size(); i++) {
		// retrieve kebabs 
		if (i == index1)
			p1 = this->rack.elementAt(index1);
		if (i == index2)
			p2 = this->rack.elementAt(index2);
	}

	// switch positions
	this->rack.insertAt(p1, index2);
	this->rack.insertAt(p2, index1);

	// remove kebabs from previous positions
	// edge case: index2 is the last kebab
	if (index2 == this->rack.size() - 3) {
		this->rack.removeAt(index2 + 1);
		this->rack.removeAt(index1 + 1);
	} else { // general case
		this->rack.removeAt(index1 + 1);
		this->rack.removeAt(index2 + 1);
	}
	return true;
}

Kebab* Grill::request(unsigned int pos) {
	// convert to 0 based indexing
	unsigned int index = pos - 1; 
	// retrieve element at index (NULL if index is invalid)
	Kebab* ret = this->rack.elementAt(index); 
	// remove kebab at index
	this->rack.removeAt(index);
	return ret;
}

Kebab* Grill::request(Kebab& r) {
	// if this rack contains the requested kebab
	if (this->rack.contains(r)) {
		// traverse through list
		for (unsigned int i = 0; i < this->rack.size(); i++) {
			// find the requested kebab
			if (this->rack.elementAt(i)->hasSameIngredients(r)) {
				// return the kebab and remove it
				Kebab* ret = this->rack.elementAt(i);
				this->rack.removeAt(i);
				return ret;
			}
		}
	}
	return NULL;
}

void Grill::addKebab(Kebab& n) {
	this->rack.insertBack(&n);
}

void Grill::sortByMeat() {
	// selection sort
	// find kebab with max meats
	for (unsigned int a = 0; a < this->rack.size(); a++) {
		unsigned int initial = a;
		Kebab* seed = this->rack.elementAt(a);
		for (unsigned int i = initial + 1; i < this->rack.size(); i++) {
			// find kebab + position with max num meats
			if (seed->numMeats() < this->rack.elementAt(i)->numMeats()) {
				seed = this->rack.elementAt(i);
				initial = i;
			}
		}
		// seed now contains kebab with max num meats
		// swap using 1-based indexing
		this->swap(initial + 1, a + 1);
	}
}

std::vector<std::string> Grill::showKebabs() const {
	std::vector<std::string> ret(this->rack.size());
	for (unsigned int i = 0; i < this->rack.size(); i++)
		ret[i] = this->rack.elementAt(i)->listIngredients();
	return ret;
}
