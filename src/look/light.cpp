#include "light.h"

light::light() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	color = glm::vec3(1.0f);
	intensity = 0.9f;
}

void light::set_intensity(const float& i) {
	intensity = i;
}

float light::get_intensity() const {
	return intensity;
}

glm::vec3 light::get_color() const {
	return color;
}

