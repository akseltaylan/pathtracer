#include "ray.h"

ray::ray(glm::vec3 pp, glm::vec3 vv) : p(pp), v(vv) {}

glm::vec3 ray::evaluate(float t) const {
	return p + (v * t);
}