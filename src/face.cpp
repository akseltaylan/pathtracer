#include "face.h"

face::face(std::vector<int> pIdxs, std::vector<int> uvIdxs, std::vector<int> nIdxs) {
	this->pts = pIdxs;
	this->uvs = uvIdxs;
	this->normals = nIdxs;
}

vec4 face::get_normal(std::vector<vec4> vertices, bool isNormalized) {
	vec4 v0 = vertices[pts[0]];
	vec4 v1 = vertices[pts[1]];
	vec4 v2 = vertices[pts[2]];
	vec4 A = v1 - v0;
	vec4 B = v2 - v0;
	vec4 C = A.cross(B);
	if (isNormalized) C.normalize();
	return C;
}