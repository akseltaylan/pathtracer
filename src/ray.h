#ifndef RAY_H
#define RAY_H

#include "vec4.h"

class ray {
	public:
		vec4 p;		// starting point
		vec4 v;		// direction
		bool isShadowRay;

		ray() {};
		ray(vec4, vec4);
		vec4 evaluate(float);
};

#endif