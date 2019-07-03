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
	extents scene_ex;
	s = ss;
	for (int i = 0; i < s->get_objs().size(); ++i) {
		extents * e = new extents();		
		for (int j = 0; j < num_plane_normals; ++j) {
			std::vector<float> d_vals = { 0.0f, 0.0f };
			s->get_objs()[i]->compute_bounds(plane_set_normals[j], d_vals);
			e->d[j] = d_vals;
		}
		e->obj = s->get_objs()[i];
		exs.push_back(e);
		scene_ex.enlarge(*exs[i]);
	}
	oct = new octree(scene_ex);
	for (int i = 0; i < s->get_objs().size(); ++i) {
		oct->insert(oct->root, exs[i], oct->bounds[0], oct->bounds[1], 0);
	}
	oct->build(oct->root, oct->bounds[0], oct->bounds[1]);
}

bvh::~bvh() {
	/*
	for (int i = 0; i < exs.size(); ++i) {
		free(exs[i]);
	}*/
}

const object * bvh::intersect(const ray & r, float t_c) const {
	float t_closest = t_c;
	const object * hit = nullptr;
	std::vector<float> numers, denoms;
	for (int i = 0; i < num_plane_normals; ++i) {
		numers.push_back(glm::dot(plane_set_normals[i], r.p));
		denoms.push_back(glm::dot(plane_set_normals[i], r.v));
	}
	/*
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
	*/
	int plane_idx = 0;
	float t_n = 0;
	float t_f = t_c;
	if (!oct->root->extents.intersect(r, denoms, numers, t_n, t_f, plane_idx)
		|| t_f < 0 || t_n > t_c) {
		return nullptr;
	}
	float t_m = t_f;
	std::priority_queue<queue_elem> queue;
	queue.push(queue_elem(oct->root, 0.0f));
	while (!queue.empty() && queue.top().t < t_m) {
		const octree_node * node = queue.top().node;
		queue.pop();
		if (node->is_leaf) {
			for (int i = 0; i < node->data.size(); ++i) {
				float t = t_f;
				if (node->data[i]->obj->intersect(r, t)) {
					if (t < t_m) {
						t_m = t;
						hit = node->data[i]->obj;
					}
				}
			}
		}
		else {
			for (int i = 0; i < 8; ++i) {
				if (node->children[i] != nullptr) {
					float t_near_child = 0, t_far_child = t_f;
					if (node->children[i]->extents.intersect(r, denoms, numers, t_near_child, t_far_child, plane_idx)) {
						float t = (t_near_child < 0 && t_far_child >= 0) ? t_far_child : t_near_child;
						queue.push(queue_elem(node->children[i], t));
					}
				}
			}
		}
	}
	return hit;
}