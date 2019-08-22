#ifndef AREA_LIGHT_H
#define AREA_LIGHT_H

#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "light.h"
#include "../geo/mesh.h"
#include <random>

class area_light: public light {
	public:
		area_light();
		area_light(const glm::vec3&, const float&, const glm::vec3&);
		glm::vec3 get_pos() const;
		
		mesh * area;
};

#endif
