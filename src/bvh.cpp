#include "bvh.h"

const std::vector<glm::vec3> bvh::plane_set_normals = {
	glm::vec3(1, 0, 0),
	glm::vec3(0, 1, 0),
	glm::vec3(0, 0, 1),
	glm::vec3(sqrtf(3) / 3.0f, sqrtf(3) / 3.0f, sqrtf(3) / 3.0f),
	glm::vec3(-sqrtf(3) / 3.0f, sqrtf(3) / 3.0f, sqrtf(3) / 3.0f),
	glm::vec3(-sqrtf(3) / 3.0f, -sqrtf(3) / 3.0f, sqrtf(3) / 3.0f),
	glm::vec3(sqrtf(3) / 3.0f, -sqrtf(3) / 3.0f, sqrtf(3) / 3.0f)
};

bvh::bvh() {
	s = nullptr;
}

bvh::bvh(scene * ss) {
	s = ss;
	for (int i = 0; i < s->get_objs().size(); ++i) {
		extents * e = new extents();		
		for (int j = 0; j < num_plane_normals; ++j) {
			std::vector<float> d_vals = { 0.0f, 0.0f };
			s->get_objs()[i]->compute_bounds(plane_set_normals[j], d_vals);
			e->d[j] = d_vals;
		}
		exs.push_back(e);
	}
}

bvh::~bvh() {
	/*
	for (int i = 0; i < exs.size(); ++i) {
		free(exs[i]);
	}*/
}

const object * bvh::intersect(const ray & r, float t_c) {
	float t_closest = t_c;
	object * hit = nullptr;
	std::vector<float> numers, denoms;
	for (int i = 0; i < num_plane_normals; ++i) {
		numers.push_back(glm::dot(plane_set_normals[i], r.p));
		denoms.push_back(glm::dot(plane_set_normals[i], r.v));
	}
	for (int i = 0; i < exs.size(); ++i) {
		float t_n = -k_infinity;
		float t_f = k_infinity;
		int plane_idx;
		if (exs[i]->intersect(r, denoms, numers, t_n, t_f, plane_idx)) {
			if (t_n < t_closest) {
				t_closest = t_n;
				hit = s->get_objs()[i];
			}
		}
	}
	return hit;
}