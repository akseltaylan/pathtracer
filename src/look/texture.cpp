#include "texture.h"

texture::texture() {
	pixels = new glm::vec3*[2];
	for (int i = 0; i < 2; ++i) {
		pixels[i] = new glm::vec3[2];
		for (int j = 0; j < 2; ++j) {
			pixels[i][j] = glm::vec3(0.0f);
		}
	}
}

texture::texture(const char * filename) {
	read_file(filename);
}

texture::~texture() {
	for (int i = 0; i < width; ++i) {
		delete[] pixels[i];
	}
	delete pixels;
}

// read ppm file, get pixel color data and place in pixel buffer
void texture::read_file(const char * filename) {
	
	// read in file
	FILE * file = fopen(filename, "r");

	if (file == NULL) {
		perror(NULL);
		std::cerr << "Unable to open file!" << std::endl;
		return;
	}
	char line[128];
	int lines = 2;
	float rgb_divider = 1.0f;
	std::vector<float> rgb_values;
	while (fgets(line, sizeof(line), file)) {
		if (lines > 0) {
			--lines;
			continue;
		}
		std::stringstream ss;
		if (lines == 0) {
			ss << line;
			std::string w, h;
			ss >> w >> h;
			width = stoi(w);
			height = stoi(h);
			--lines;
			continue;
		}
		if (lines == -1) {
			ss << line;
			std::string rgb_type;
			ss >> rgb_type;
			rgb_divider = stof(rgb_type);
			--lines;
			continue;

		}
		ss << line;
		std::string val;
		ss >> val;
		rgb_values.push_back(stof(val) / rgb_divider);
	}
	pixels = new glm::vec3*[width];
	int rgb_idx = 0;
	for (int i = 0; i < width; ++i) {
		pixels[i] = new glm::vec3[height];
		for (int j = 0; j < height; ++j) {
			glm::vec3 pixel;
			int checker = 0;
			while (checker < 3) {
				pixel[checker] = rgb_values[rgb_idx];
				++checker;
				++rgb_idx;
			}
			pixels[i][j] = pixel;
		}
	}
}

glm::vec3 texture::pixel_helper(int x, int y) {
	x %= width;
	y %= height;
	return pixels[x][y];
}

glm::vec3 texture::get_color_at(glm::vec2 uv_coords) {
	// based on UV coordinates, return color from pixel buffer
	float u = uv_coords.x;
	float v = 1 - uv_coords.y;
	int i = (int)(u*width);
	if (i == width) i -= 1;
	int j = (int)(v*height);
	if (j == height) j -= 1;
	i = abs(i);
	j = abs(j);
	float uP = u - (float)i / width;
	float vP = v - (float)j / height;
	return pixel_helper(i, j)*(1 - uP)*(1 - vP) +
		pixel_helper((i + 1), j)*uP*(1 - vP) +
		pixel_helper(i, (j + 1))*(1 - uP)*vP +
		pixel_helper((i + 1), (j + 1))*uP*vP;
	
}