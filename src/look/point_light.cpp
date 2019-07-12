#include "point_light.h"

point_light::point_light() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
}

point_light::point_light(const glm::vec3& pos, const float& i, const glm::vec3& col) {
	position = pos;
	intensity = i;
	color = col;
}

// getter

glm::vec3 point_light::get_pos() const {
	return position;
}

