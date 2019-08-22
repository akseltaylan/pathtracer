#include "material.h"

material::material() {
	ka = 0.0f;
	kd = 0.0f;
	ks = 0.0f;
	alpha = 0.0f;
	tex = nullptr;
	emissive = glm::vec3(0.0f);
	mtype = mat_type::diffuse;
}

material::material(const float& _ka, const float& _kd, const float& _ks, const float& _alpha, const glm::vec3& alb) {
	ka = _ka;
	kd = _kd;
	ks = _ks;
	alpha = _alpha;
	albedo = alb;
	tex = nullptr;
	emissive = glm::vec3(0.0f);
	mtype = mat_type::diffuse;
}

material::material(const float& _ka, const float& _kd, const float& _ks, const float& _alpha, const glm::vec3& alb, const glm::vec3& em, mat_type mt) {
	ka = _ka;
	kd = _kd;
	ks = _ks;
	alpha = _alpha;
	albedo = alb;
	tex = nullptr;
	emissive = em;
	mtype = mt;
}

void material::set_texture(texture * t) {
	tex = t;
}

void material::set_albedo(glm::vec3 col) {
	albedo = col;
}

glm::vec3 material::get_albedo(glm::vec2 uv_coords) {
	if (tex == nullptr) {
		return albedo;
	}
	else {
		return tex->get_color_at(uv_coords);
	}

}
