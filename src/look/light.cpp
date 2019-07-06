#include "light.h"

light::light() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	ia = glm::vec3(0.0f, 0.0f, 0.0f);
	id = glm::vec3(0.0f, 0.0f, 0.0f);
	is = glm::vec3(0.0f, 0.0f, 0.0f);
}

light::light(const glm::vec3& pos) : position(pos) {}

void light::set_intensity(const glm::vec3& _ia, const glm::vec3& _id, const glm::vec3& _is) {
	ia = _ia;
	id = _id;
	is = _is;
}

glm::vec3 light::get_intensity(const char& which_int) {
	switch (which_int) {
		case 'a': return ia;
		case 'd': return id;
		case 's': return is;
		default: return glm::vec3(0.0f);
	}
}

