#include "implane.h"

const std::vector<float> implane::jitter_matrix = {
	-1.0 / 4.0,  3.0 / 4.0,
	 3.0 / 4.0,  1.0 / 3.0,
	-3.0 / 4.0, -1.0 / 4.0,
	 1.0 / 4.0, -3.0 / 4.0,
};

implane::implane() {
	width = 500;
	height = 500;
	cur_x = 0;
	cur_y = 0;
	center = glm::vec3(0.0f, 0.0f, 0.0f);
}

implane::implane(int w, int h) : width(w), height(h) {
	cur_x = 0;
	cur_y = 0;
	center = glm::vec3(0.0f, 0.0f, 100.0f);
}

glm::vec3 implane::nextpixel(const int& sample, const int& i, const int& j) {
	/*
	double xdist = width * ((cur_x + 1.0) / width - 0.5);
	double ydist = height * ((cur_y + 1.0) / height - 0.5);
	++cur_x;
	if (cur_x == width) {
		cur_x = 0;
		++cur_y;
	}
	return glm::vec3(xdist, ydist, 0.0);*/
	float x = width * ((i + jitter_matrix[2 * sample]) / width - 0.5);
	float y = height * ((j + jitter_matrix[2 * sample + 1]) / height - 0.5);
	return glm::vec3(x, y, 0.0);
}

