#ifndef CS221_HSLAPIXEL_H
#define CS221_HSLAPIXEL_H

#include <string>
#include <vector>

using namespace std;

namespace cs221util {
	class HSLAPixel {
		public:
			double h, s, l, a;
			HSLAPixel();
			HSLAPixel(double h, double s, double l);
			HSLAPixel(double h, double s, double l, double a);
	};
}

#endif
