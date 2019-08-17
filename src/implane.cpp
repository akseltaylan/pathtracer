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
}

implane::implane(int w, int h) : width(w), height(h) {
	cur_x = 0;
	cur_y = 0;
}

glm::vec3 implane::nextpixel(const int& sample, const int& j, const int& i) {
	float x = width * ((j + jitter_matrix[2 * sample]) / width - 0.5);
	float y = height * ((i + jitter_matrix[2 * sample + 1]) / height - 0.5);
	return glm::vec3(x, y, 0.0);
}

