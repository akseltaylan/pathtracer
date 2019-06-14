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
#include "scene.h"
#include "mat4.h"

class pathtracer {
	public:
		image * img;
		vec4 eyept;
		scene * s;

		pathtracer();
		pathtracer(image*);

		void set_scene(scene *);
		void render();
		Sphere * trace(ray&, float&);
		vec4 cast(ray&);
};

#endif