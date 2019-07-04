#include "face.h"

face::face(std::vector<int> pIdxs, std::vector<int> uvIdxs, std::vector<int> nIdxs) {
	this->pts = pIdxs;
	this->uvs = uvIdxs;
	this->normals = nIdxs;
	normal = glm::vec3(0.0f, 0.0f, 0.0f);
}

void face::set_normal(std::vector<glm::vec3> vertices, bool isNormalized) {
	v0 = vertices[pts[0]];
	v1 = vertices[pts[1]];
	v2 = vertices[pts[2]];
	A = v1 - v0;
	B = v2 - v0;
	glm::vec3 C = glm::cross(A, B);
	if (isNormalized) C = glm::normalize(C);
	normal = C;
}

glm::vec3 face::get_normal(std::vector<glm::vec3> vertices, bool isNormalized) {
	if (normal != glm::vec3(0.0f, 0.0f, 0.0f)) {
		set_normal(vertices, isNormalized);
	}
	return normal;
}

glm::vec3 face::get_normal() {
	return normal;
}