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
		double length() const;
		double dot(vec4& vec);
		vec4 cross(vec4& vec);
		void normalize();
		void clamp(double low, double high);

		bool operator==(const vec4& v);
		bool operator!=(const vec4& v);
		bool operator<(const vec4& v);
		bool operator<=(const vec4& v);
		bool operator>(const vec4& v);
		bool operator>=(const vec4& v);

		vec4 & operator=(const vec4& v);
		vec4 & operator+=(const vec4& v);
		vec4 & operator-=(const vec4& v);
		vec4 & operator=(const double c);
		vec4 & operator+=(const double c);
		vec4 & operator-=(const double c);
		vec4 & operator*=(const double c);
		//vec4 & operator*=(const mat4& m);

		friend std::ostream& operator<<(std::ostream& os, vec4& v);
};

#endif
