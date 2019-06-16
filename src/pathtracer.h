#ifndef PATHTRACER_H
#define PATHTRACER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "image.h"
#include "implane.h"
#include "ray.h"
#include "vec2.h"
#include "scene.h"
#include "mat4.h"
#include <chrono>

class pathtracer {
	public:
		image * img;
		glm::vec3 eyept;
		scene * s;
		int num_rays = 0;

		pathtracer();
		pathtracer(image*);

		void set_scene(scene *);
		void render();
		object * trace(const std::vector<object*>&, const ray&, float&);
		glm::vec3 cast(const std::vector<object*>&, const ray&);
};

#endif