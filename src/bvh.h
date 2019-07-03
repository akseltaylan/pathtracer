#ifndef BVH_H
#define BVH_H

#include <vector>
#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "scene.h"
#include "extents.h"
#include "object.h"
#include <queue>
#include "octree.h"

class bvh {
	private:
		static const int num_plane_normals = 7;
		static const std::vector<glm::vec3> plane_set_normals;
		std::vector<extents *> exs;
	public:
		scene * s;
		octree * oct;
		bvh();
		bvh(scene*);
		const object* intersect(const ray &, float) const;
		~bvh();
};

#endif