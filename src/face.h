#ifndef FACE_H
#define FACE_H

#include <vector>
#include "vec4.h"
#include "vec2.h"

class face {
	public:
		// hold indices to pts, normals, and uvs within the corresponding obj_mesh
		std::vector<int> pts;
		std::vector<int> normals;
		std::vector<int> uvs;

		face(std::vector<int>, std::vector<int>, std::vector<int>);

		vec4 get_normal(std::vector<vec4>, bool);

	private:
		bool isQuad;

};

#endif