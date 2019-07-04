#ifndef OCTREE_H
#define OCTREE_H

#include <vector>
#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../ray.h"
#include <iostream>
#include "../geo/object.h"
#include <algorithm>
#include "bbox.h"

struct octree_node {
	std::vector<octree_node*> children;
	std::vector<const bbox*> data;
	bbox bbox;
	bool is_leaf;
	octree_node() : is_leaf(true) {
		children = std::vector<octree_node*>(8, nullptr);
	}
	~octree_node() {
		for (int i = 0; i < 8; ++i) {
			if (children[i] != nullptr) {
				delete children[i];
			}
		}
	}
};

// wrapper for octree noodes to be sorted in a pqueue based on their t value
struct t_entity {
	const octree_node * node;
	float t;
	t_entity(const octree_node * _node, float _t) {
		node = _node;
		t = _t;
	}
	friend bool operator < (const t_entity &a, const t_entity &b) {
		return a.t > b.t;
	}
};

class octree {
	
	private:

	public:
		octree_node * root;
		std::vector<glm::vec3> bounds;

		octree(const bbox &);
		~octree();
		void insert(octree_node *, const bbox *, glm::vec3, glm::vec3, int);
		void child_bound(const int &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, glm::vec3 &, glm::vec3&) const;
		void build_tree(octree_node *, const glm::vec3&, const glm::vec3&);
};

#endif