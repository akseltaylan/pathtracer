#ifndef PATHTRACER_H
#define PATHTRACER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "image.h"
#include "implane.h"
#include "ray.h"
#include "math/vec2.h"
#include "geo/mesh.h"
#include "scene.h"
#include "math/mat4.h"
#include "accel/bvh.h"
#include <chrono>
#include <thread>
#include <atomic>
#include <future>
#include "omp.h"

class pathtracer {
	public:
		image * img;
		glm::vec3 eyept;
		bvh * accel_struct;
		int num_rays = 0;
		float * pixels;

		pathtracer();
		pathtracer(image*);

		void set_scene(scene *);
		void render();
		bool trace(const std::vector<object*>&, const ray&, float&);
		glm::vec3 cast(const std::vector<object*>&, const ray&);
};

#endif