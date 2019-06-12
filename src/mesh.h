#ifndef MESH_H
#define MESH_H

#include "vec4.h"
#include "vec2.h"
#include "face.h"
#include <vector>

class mesh {
	public:
		std::vector<vec4> vertices;
		std::vector<vec2> uvs;
		std::vector<vec4> normals;
		std::vector<face> faces;

		mesh();
		void debug();
};
#endif