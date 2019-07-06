#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "light.h"

class point_light: public light {
	point_light();
	point_light(glm::vec3, glm::vec3);
	glm::vec3 get_pos();
};

#endif
