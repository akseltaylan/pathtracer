#ifndef PATHTRACER_H
#define PATHTRACER_H

#define GLEW_STATIC
#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>
#include "image.h"
#include "implane.h"
#include "ray.h"
#include "math/utils.h"
#include "geo/mesh.h"
#include "scene.h"
#include "accel/bvh.h"
#include <chrono>
#include <time.h>
#include <stdlib.h>
#include <random>

#define PIXEL_DEBUG false
#define PI 3.14159265354f

class pathtracer {
	public:
		image * img;
		glm::vec3 eyept;
		scene * s;
		bvh * accel_struct;
		long long int num_rays = 0;
		float * pixels;
		int samples;

		pathtracer();
		pathtracer(image*);

		// setter
		void set_scene(scene *);

		// lighting/shading
		void shade_coord_system(const glm::vec3&, glm::vec3&, glm::vec3&);
		glm::vec3 get_uniform_hemisphere_sample(const float&, const float&);
		glm::vec3 convert_sample(const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&);
		ray reflect(const ray&, const glm::vec3&, const glm::vec3&);
		ray refract(const ray&, const glm::vec3&, const float&, const float&);
		void fresnel(const ray&, const glm::vec3&, const float&, const float&, float&);

		// core rendering functionality
		void render();
		const object * trace(const ray&, float&, int&, float&, float&);
		glm::vec3 cast(const ray&, const int&, unsigned short*);
		float rand_gen(short unsigned *);
};

#endif