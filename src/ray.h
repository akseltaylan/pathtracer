#ifndef RAY_H
#define RAY_H

#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ray {
	public:
		glm::vec3 p;		// starting point
		glm::vec3 v;		// direction
		bool isShadowRay;

		ray() {};
		ray(glm::vec3, glm::vec3);
		glm::vec3 evaluate(float) const;
};

#endif