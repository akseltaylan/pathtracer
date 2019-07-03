#include "octree.h"

octree::octree(const extents &ex) {
	root = new octree_node;

	float x_diff = ex.d[0][1] - ex.d[0][0];
	float y_diff = ex.d[1][1] - ex.d[1][0];
	float z_diff = ex.d[2][1] - ex.d[2][0];
	float dim = std::max(x_diff, std::max(y_diff, z_diff));
	glm::vec3 centroid(
		ex.d[0][0] + ex.d[0][1],
		ex.d[1][0] + ex.d[1][1],
		ex.d[2][0] + ex.d[2][1]
	);
	bounds.push_back(glm::vec3(centroid - glm::vec3(dim)) * 0.5f);
	bounds.push_back(glm::vec3(centroid + glm::vec3(dim)) * 0.5f);
}

void octree::insert(octree_node * node, const extents * ex, glm::vec3 min_b, glm::vec3 max_b, int depth) {
	if (node->is_leaf) {
		if (node->data.size() == 0 || depth == 16) {
			node->data.push_back(ex);
		}
		else {
			node->is_leaf = false;
			while (node->data.size()) {
				insert(node, node->data.back(), min_b, max_b, depth);
				node->data.pop_back();
			}
			insert(node, ex, min_b, max_b, depth);
		}
	}
	else {
		glm::vec3 ex_centroid(
			(glm::vec3(ex->d[0][0], ex->d[1][0], ex->d[2][0]) +
			glm::vec3(ex->d[0][1], ex->d[1][1], ex->d[2][1])) * 0.5f
		);
		glm::vec3 node_centroid = (min_b + max_b) * 0.5f;
		int child_idx = 0;
		if (ex_centroid[0] > node_centroid[0]) child_idx += 4;
		if (ex_centroid[1] > node_centroid[1]) child_idx += 2;
		if (ex_centroid[2] > node_centroid[2]) child_idx += 1;
		glm::vec3 child_min_b;
		glm::vec3 child_max_b;
		glm::vec3 bound_centroid = (min_b + max_b) * 0.5f;
		// compute child bound
		child_bound(child_idx, bound_centroid, min_b, max_b, child_min_b, child_max_b);
		if (node->children[child_idx] == nullptr) {
			node->children[child_idx] = new octree_node;			
		}
		insert(node->children[child_idx], ex, child_min_b, child_max_b, depth + 1);
			
	}
}

void octree::child_bound(const int & idx, const glm::vec3 & bound_centroid, const glm::vec3 & b_min,
						 const glm::vec3 & b_max, glm::vec3 & p_min, glm::vec3 & p_max) const {
	p_min[0] = (idx & 4) ? bound_centroid[0] : b_min[0];
	p_max[0] = (idx & 4) ? b_max[0] : bound_centroid[0];
	p_min[1] = (idx & 2) ? bound_centroid[1] : b_min[1];
	p_max[1] = (idx & 2) ? b_max[1] : bound_centroid[1];
	p_min[2] = (idx & 1) ? bound_centroid[2] : b_min[2];
	p_max[2] = (idx & 1) ? b_max[2] : bound_centroid[2];
}

void octree::build(octree_node * node, const glm::vec3 & b_min, const glm::vec3 & b_max) {
	if (node->is_leaf) {
		for (int i = 0; i < node->data.size(); ++i) {
			node->extents.enlarge(*node->data[i]);
		}
	}
	else {
		for (int i = 0; i < 8; ++i) {
			if (node->children[i]) {
				glm::vec3 child_b_min, child_b_max;
				glm::vec3 bound_centroid = (b_min + b_max) * 0.5f;
				child_bound(i, bound_centroid, b_min, b_max, child_b_min, child_b_max);
				build(node->children[i], child_b_min, child_b_max);
				node->extents.enlarge(node->children[i]->extents);
			}
		}
	}
}

octree::~octree() {
	delete root;
}