#include "area_light.h"

area_light::area_light() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	intensity = 0.9f;
	color = glm::vec3(1.0f);
}

area_light::area_light(const glm::vec3& pos, const float& i, const glm::vec3& col) {
	position = pos;
	intensity = i;
	color = col;
}

// getter

glm::vec3 area_light::get_pos() const {
	return position;
}

