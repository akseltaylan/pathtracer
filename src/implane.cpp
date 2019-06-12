#include "implane.h"

implane::implane() {
	width = 500;
	height = 500;
}

implane::implane(int w, int h) : width(w), height(h) {}

vec4 implane::nextpixel() {
	float xdist = width * ((cur_x + 1.0f) / width - 0.5f);
	float ydist = height * ((cur_y + 1.0f) / height - 0.5f);
	++cur_x;
	if (cur_x == width) {
		cur_x = 0;
		++cur_y;
	}
	return vec4(xdist, ydist, 0.0f);
}

