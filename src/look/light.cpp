#include "light.h"

light::light() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	color = glm::vec3(0.2f, 0.1, 0.0f);
}

light::light(glm::vec3 pos, glm::vec3 col) : position(pos), color(col) {}

// getter

glm::vec3 light::get_col() {
	return color;
}

