#include "material.h"

material::material() {
	ka = 0.0f;
	kd = 0.0f;
	ks = 0.0f;
	alpha = 0.0f;
}

material::material(const float& _ka, const float& _kd, const float& _ks, const float& _alpha) {
	ka = _ka;
	kd = _kd;
	ks = _ks;
	alpha = _alpha;
}
