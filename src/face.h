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

		face(std::vector<int> pIdxs, std::vector<int> uvIdxs, std::vector<int> nIdxs) {
			this->pts = pIdxs;
			this->uvs = uvIdxs;
			this->normals = nIdxs;
		};
		~face() {};

	private:
		bool isQuad;

};

#endif