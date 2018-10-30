#ifndef VEC4_H
#define VEC4_H

#include <iostream>
#include <math.h>

/*
	3D vector class
*/

class vec4 {

	public:

		double x;
		double y;
		double z;
		double w;
		vec4();
		vec4(double a);
		vec4(double xx, double yy, double zz);
		vec4(double xx, double yy, double zz, double ww);
		double length();
		double dot(vec4& vec);
		vec4 cross(vec4& vec);
		void normalize();
		void clamp(double low, double high);

		bool operator==(const vec4& v);

		friend std::ostream& operator<<(std::ostream& os, vec4& v);
};

#endif
