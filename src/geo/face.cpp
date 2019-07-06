#include "face.h"

face::face(std::vector<int> pIdxs, std::vector<int> uvIdxs, std::vector<int> nIdxs) {
	this->pts = pIdxs;
	this->uvs = uvIdxs;
	this->normals = nIdxs;
	normal = glm::vec3(0.0f, 0.0f, 0.0f);
}

void face::set_normal(std::vector<glm::vec3> vertices, bool is_normalized) {
	v0 = vertices[pts[0]];
	v1 = vertices[pts[1]];
	v2 = vertices[pts[2]];
	A = v1 - v0;
	B = v2 - v1;
	glm::vec3 C = glm::cross(A, B);
	if (is_normalized) C = normalize(C);
	normal = C;
}

glm::vec3 face::get_normal(std::vector<glm::vec3> vertices, bool is_normalized) {
	set_normal(vertices, is_normalized);
	return normal;
}

glm::vec3 face::get_normal() {
	return normal;
}