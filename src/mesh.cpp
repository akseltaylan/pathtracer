#include "mesh.h"

mesh::mesh() {
	vertices = std::vector<vec4>();
	uvs = std::vector<vec2>();
	normals = std::vector<vec4>();
}

void mesh::debug() {
	std::cout << "total vertex count: " << vertices.size() << std::endl;
	std::cout << "total faces count: " << faces.size() << std::endl;
}

bool mesh::rayTriangleIntersect(ray r, face f, float &t) {

	// compute triangle's normal
	vec4 normal = f.get_normal(vertices, false);

	// test if ray and triangle are parallel - if so, fails, RETURN false
	float denom = normal.dot(r.v);
	if (denom == 0) return false;

	// compute t, from which we compute the intersection point P
	float D = normal.dot(vertices[f.pts[0]]);
	float numer = normal.dot(r.p) + D;
	t = numer / denom;
	if (t < 0) return false;

	// test if P is on the left side of each one of the triangle's edges
	vec4 phit = r.evaluate(t);

	// if inside out-test succeeds, RETURN true
	vec4 edge_0 = vertices[f.pts[1]] - vertices[f.pts[0]];
	vec4 edge_1 = vertices[f.pts[2]] - vertices[f.pts[1]];
	vec4 edge_2 = vertices[f.pts[0]] - vertices[f.pts[2]];
	vec4 c0 = phit - vertices[f.pts[0]];
	vec4 c1 = phit - vertices[f.pts[1]];
	vec4 c2 = phit - vertices[f.pts[2]];
	if (normal.dot(edge_0.cross(c0)) > 0 &&
		normal.dot(edge_1.cross(c1)) > 0 &&
		normal.dot(edge_2.cross(c2)) > 0) return true;
	
	return false;
}

bool mesh::intersect(ray r, float& tNear) {
	float t = std::numeric_limits<float>::max();
	bool intersection = false;
	for (face f : faces) {
		if (rayTriangleIntersect(r, f, t) && t < tNear) {
			tNear = t;
			intersection |= true;
		}
	}

	return intersection;
}

