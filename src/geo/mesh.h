#ifndef MESH_H
#define MESH_H

#define GLEW_STATIC
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../math/vec2.h"
#include "../math/utils.h"
#include "object.h"
#include "../ray.h"
#include "face.h"
#include <algorithm>
#include <vector>
#include <chrono>

#define DEBUG true
#define MESH_DEBUG false

class mesh : public object {
	public:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		int num_tris;
		std::vector<int> v_idxs;
		std::vector<int> uv_idxs;
		std::vector<int> n_idxs;
		std::vector<face> faces;

		//TODO: will have a material 
		mesh(const char *);
		bool get_data(const char *);
		void debug(const char *);
		bool ray_triangle_intersect(const ray&, const glm::vec3&, const glm::vec3&, const glm::vec3&, float&, float&, float&) const;
		bool intersect(const ray&, float&, int&, float&, float&) const;
		void compute_bounds(glm::vec3, std::vector<float>&) const;
		void get_shading_properties(glm::vec3&, glm::vec3&, const float&, const float&, const float&, const int&, const ray&, glm::vec2&) const;
		void populate_normals();
		void set_to_origin();
};

#endif