#ifndef BBOX_H
#define BBOX_H

#include <vector>
#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../ray.h"
#include <iostream>
#include "../geo/object.h"

static const float k_infinity = std::numeric_limits<float>::max();

class bbox {
	
	private:
		static const int num_plane_normals = 7;

	public:
		bbox();
		std::vector< std::vector<float> > d;
		bool intersect(const ray &, std::vector<float>, std::vector<float>, float &, float &, int &);
		void enlarge(const bbox &);
		const object * obj;
	
};

#endif