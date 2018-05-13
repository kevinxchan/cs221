#include <iostream>
#include <cmath>
#include <cstdlib>
#include "HSLAPixel.h"

namespace cs221util {

	HSLAPixel::HSLAPixel() {
		this->h = 0.0;
		this->s = 0.0;
		this->l = 1.0;
		this->a = 1.0;
	};

	HSLAPixel::HSLAPixel(double h, double s, double l) {
		this->h = h;
		this->s = s;
		this->l = l;
		this->a = 1.0;
	};

	HSLAPixel::HSLAPixel(double h, double s, double l, double a) {
		this->h = h;
		this->s = s;
		this->l = l;
		this->a = a;
	};
}
