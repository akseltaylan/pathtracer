#include "ray.h"

ray::ray(vec4 pp, vec4 vv) : p(pp), v(vv) {}

vec4 ray::evaluate(float t) {
	vec4 result;
	result.x = p.x + v.x * t;
	result.y = p.y + v.y * t;
	result.z = p.z + v.z * t;
	return result;
}