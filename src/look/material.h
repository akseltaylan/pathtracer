#ifndef MATERIAL_H
#define MATERIAL_H

#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class material {
	public:
		float ka;
		float kd;
		float ks;
		float alpha;
		material();
		material(const float&, const float&, const float&, const float&);
};

#endif
