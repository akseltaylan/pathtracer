#include "point_light.h"

point_light::point_light() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	color = glm::vec3(0.2f, 0.1, 0.0f);
}

point_light::point_light(glm::vec3 pos, glm::vec3 col) {
	position = pos;
	color = col;
}

// getter

glm::vec3 point_light::get_pos() {
	return position;
}

