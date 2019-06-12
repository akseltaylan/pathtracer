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