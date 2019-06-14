#include "implane.h"

implane::implane() {
	width = 500;
	height = 500;
	cur_x = 0;
	cur_y = 0;
	center = vec4(0.0f, 0.0f, 0.0f);
}

implane::implane(int w, int h) : width(w), height(h) {
	cur_x = 0;
	cur_y = 0;
	center = vec4(0.0f, 0.0f, 0.0f);
}

vec4 implane::nextpixel() {
	double xdist = width * ((cur_x + 1.0) / width - 0.5);
	double ydist = height * ((cur_y + 1.0) / height - 0.5);
	++cur_x;
	if (cur_x == width) {
		cur_x = 0;
		++cur_y;
	}
	return vec4(xdist, ydist, 0.0);
}

