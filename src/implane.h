#ifndef IMPLANE_H
#define IMPLANE_H

#include <vector>
#include "object.h"
#include "vec4.h"

class implane {
	private:
		float width;
		float height;
		vec4 center;
		int cur_x;
		int cur_y;
	public:
		implane();
		implane(int, int);
		vec4 nextpixel();
};

#endif