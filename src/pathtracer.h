#ifndef PATHTRACER_H
#define PATHTRACER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "image.h"
#include "vec4.h"
#include "vec2.h"
#include "mat4.h"

class pathtracer {
	public:
		image * img;

		pathtracer();
		pathtracer(image*);

		void render();
};

#endif