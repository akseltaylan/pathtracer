#include "utils.h"

glm::vec3 normalize(const glm::vec3& v) {
	float denom = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	return v / denom;
}

glm::vec3 reflected(const glm::vec3& v, const glm::vec3& normal) {
	return v - (2.0f * glm::dot(normal, v) * normal);
}

bool quadratic_formula(const float &a, const float &b, const float &c, float &t0, float &t1) {
	float discrem = (b * b) - (4 * a * c);
	if (discrem < 0) {
		//std::cout << "h" << std::endl;
		return false;
	}
	else if (discrem == 0) {
		t0 = t1 = -0.5f * (b / a);
	}
	else {
		float q = (b > 0) ? 0.5f * (-b + sqrt(discrem)) : 0.5f * (-b - sqrt(discrem));
		t0 = q / a;
		t1 = c / q;
	}
	return true;
}

void debug_vec3(const glm::vec3& v, const std::string& prefix) {
	std::cout << prefix << v.x << " " << v.y << " " << v.z << std::endl;
}

