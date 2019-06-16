#ifndef MESH_H
#define MESH_H

#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "vec2.h"
#include "ray.h"
#include "face.h"
#include <vector>
#include <chrono>

#define DEBUG true

class mesh {
	public:
		std::vector<glm::vec3> vertices;
		std::vector<vec2> uvs;
		std::vector<glm::vec3> normals;
		std::vector<int> v_idxs;
		std::vector<int> uv_idxs;
		std::vector<int> n_idxs;
		std::vector<face> faces;

		//TODO: will have a material 

		mesh();
		void debug();
		bool rayTriangleIntersect(const ray&, const face&, float&);
		bool intersect(const ray&, float&);
};

#endif