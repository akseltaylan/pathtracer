#ifndef OCTREE_H
#define OCTREE_H

#include <vector>
#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ray.h"
#include <iostream>
#include "object.h"
#include <algorithm>
#include "extents.h"

struct octree_node {
	std::vector<octree_node*> children;
	std::vector<const extents*> data;
	extents extents;
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

struct queue_elem {
	const octree_node * node;
	float t;
	queue_elem(const octree_node * _node, float _t) {
		node = _node;
		t = _t;
	}
	friend bool operator < (const queue_elem &a, const queue_elem &b) {
		return a.t > b.t;
	}
};
class octree {
	
	private:

	public:
		octree_node * root;
		std::vector<glm::vec3> bounds;

		octree(const extents &);
		~octree();
		void insert(octree_node *, const extents *, glm::vec3, glm::vec3, int);
		void child_bound(const int &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, glm::vec3 &, glm::vec3&) const;
		void build(octree_node *, const glm::vec3&, const glm::vec3&);
};

#endif