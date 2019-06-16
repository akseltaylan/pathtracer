#include "mesh.h"

constexpr float k_epsilon = 1e-8;

mesh::mesh() {
	vertices = std::vector<glm::vec3>();
	uvs = std::vector<vec2>();
	normals = std::vector<glm::vec3>();
}

void mesh::debug() {
	std::cout << "total vertex count: " << vertices.size() << std::endl;
	std::cout << "total faces count: " << faces.size() << std::endl;
}

bool mesh::rayTriangleIntersect(const ray& r, const face& f, float &t) {

	// compute triangle's normal 
	/*
	glm::vec3 v0 = vertices[f.pts[0]];
	glm::vec3 v1 = vertices[f.pts[1]];
	glm::vec3 v2 = vertices[f.pts[2]];
	glm::vec3 A = v1 - v0;
	glm::vec3 B = v2 - v0; */
	glm::vec3 pvec = glm::cross(r.v, f.B);
	float det = glm::dot(f.A, pvec);

	// ray and triangle are parallel if det is close to 0
	if (fabs(det) < k_epsilon) return false;

	float inv_det = 1 / det;
	glm::vec3 tvec = r.p - f.v0;
	float u = glm::dot(tvec,pvec) * inv_det;
	if (u < 0 || u > 1) return false;

	// test if ray and triangle are parallel - if so, fails, RETURN false
	/*
	float denom = glm::dot(f.normal,r.v);
	if (denom == 0) return false;*/

	glm::vec3 qvec = glm::cross(tvec,f.A);
	float v = glm::dot(r.v,qvec) * inv_det;
	if (v < 0 || u + v > 1) return false;

	t = glm::dot(f.B,qvec) * inv_det;
	return true;
	// compute t, from which we compute the intersection point
	/*
	float D = glm::dot(f.normal,f.v1);
	float numer = glm::dot(f.normal, r.p) + D;
	t = numer / denom;
	if (t < 0) return false;*/

	// test if P is on the left side of each one of the triangle's edges
	//glm::vec3 phit = r.p + r.v * t;

	// if inside out-test succeeds, RETURN true
	/*
	glm::vec3 edge_0 = vertices[f.pts[1]] - vertices[f.pts[0]];
	glm::vec3 edge_1 = vertices[f.pts[2]] - vertices[f.pts[1]];
	glm::vec3 edge_2 = vertices[f.pts[0]] - vertices[f.pts[2]];
	glm::vec3 c0 = phit - vertices[f.pts[0]];
	glm::vec3 c1 = phit - vertices[f.pts[1]];
	glm::vec3 c2 = phit - vertices[f.pts[2]];
	if (
		glm::dot(f.normal,glm::cross(edge_0,c0)) > 0 &&
		glm::dot(f.normal, glm::cross(edge_1, c1)) > 0 &&
		glm::dot(f.normal, glm::cross(edge_2, c2)) > 0) return true;
	
	return false;*/
}

bool mesh::intersect(const ray& r, float& tNear) {
	float t = std::numeric_limits<float>::max();
	bool intersection = false;
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < faces.size(); ++i) {
		if (rayTriangleIntersect(r, faces[i], t) && t < tNear) {
			tNear = t;
			intersection |= true;
		}
	}

	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = stop - start;
	if (DEBUG) std::cout << "Checked all triangles in object for intersections in " << duration.count() << " seconds" << std::endl;

	return intersection;
}

