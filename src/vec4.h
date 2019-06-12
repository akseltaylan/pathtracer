#ifndef VEC4_H
#define VEC4_H

#include <iostream>
#include <math.h>

/*
	3D vector class
*/

class vec4 {

	public:

		float x;
		float y;
		float z;
		float w;
		
		vec4();
		vec4(float a);
		vec4(float xx, float yy, float zz);
		vec4(float xx, float yy, float zz, float ww);
		float length() const;
		float dot(vec4& vec);
		vec4 cross(vec4& vec);
		void normalize();
		void clamp(float low, float high);

		bool operator==(const vec4& v);
		bool operator!=(const vec4& v);
		bool operator<(const vec4& v);
		bool operator<=(const vec4& v);
		bool operator>(const vec4& v);
		bool operator>=(const vec4& v);

		vec4 & operator=(const vec4& v);
		vec4 & operator+=(const vec4& v);
		vec4 & operator-=(const vec4& v);
		vec4 & operator=(const float c);
		vec4 & operator+=(const float c);
		vec4 & operator-=(const float c);
		vec4 & operator*=(const float c);
		//vec4 & operator*=(const mat4& m);

		friend vec4 operator-(const vec4& a, const vec4& b);
		friend vec4 operator-(const vec4& a, const float c);
		friend vec4 operator-(const float c, const vec4& a);
		friend vec4 operator+(const vec4& a, const vec4& b);
		friend vec4 operator+(const vec4& a, const float c);
		friend vec4 operator+(const float c, const vec4& a);
		//friend vec4 operator*(const mat4& m, const vec4& v);
		friend vec4 operator*(const vec4& a, const float c);
		friend vec4 operator*(const float c, const vec4& a);
		friend vec4 operator*(const vec4& a, const vec4& b);

		friend std::ostream& operator<<(std::ostream& os, vec4& v);
};

#endif
