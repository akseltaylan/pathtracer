#ifndef TEXTURE_H
#define TEXTURE_H

#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <math.h>

class texture {
	private:
		glm::vec3 ** pixels;
		int width;
		int height;
		glm::vec3 pixel_helper(int, int);
	public:
		texture();
		texture(const char *);
		~texture();
		void read_file(const char *);
		glm::vec3 get_color_at(glm::vec2);
};

#endif