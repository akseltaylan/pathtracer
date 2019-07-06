#include "point_light.h"

point_light::point_light() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
}

point_light::point_light(const glm::vec3& pos) {
	position = pos;
}

// getter

glm::vec3 point_light::get_pos() {
	return position;
}

