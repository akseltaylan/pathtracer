#ifndef IMAGE_H
#define IMAGE_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "vec4.h"

class image {
	public:
		int width;
		int height;
		float * pixels;
		GLFWwindow * pWindow;

		image();
		image(int, int);

		void draw(void);
		void clear_image();
		void set_pixel(int, int, float, float, float);
		void set_pixel(int, int, vec4);
		void create_image();
};

#endif
