#ifndef PATHTRACER_H
#define PATHTRACER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "image.h"
#include "implane.h"
#include "ray.h"
#include "vec4.h"
#include "vec2.h"
#include "mat4.h"

class pathtracer {
	public:
		image * img;
		vec4 eyept;

		pathtracer();
		pathtracer(image*);

		void render();
};

#endif