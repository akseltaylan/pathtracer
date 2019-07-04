#include "vec4.h"

// empty constructor
vec4::vec4() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 1.0f;
}

// initialize entire vector with one value
vec4::vec4(float a) {
	x = a;
	y = a;
	z = a;
	w = a;
}

// basic constructor
vec4::vec4(float xx, float yy, float zz) {
	x = xx;
	y = yy;
	z = zz;
	w = 1.0f;
}

// includes w value
vec4::vec4(float xx, float yy, float zz, float ww) {
	// check if w can divide the other values
	if (ww != 0.0f) {
		x = xx / ww;
		y = yy / ww;
		z = zz / ww;
		w = 1.0f;
	}
	else {
		x = xx;
		y = yy;
		z = zz;
		w = ww;
	}
}

// magnitude of vector
float vec4::length() const {
	return sqrt((x*x) + (y*y) + (z*z));
}

// dot product of vector
float vec4::dot(vec4& vec) {
	return (x * vec.x) + (y * vec.y) + (z * vec.z);
}

// cross product of vector
vec4 vec4::cross(vec4& vec) {
	float newx = (y * vec.z) - (z * vec.y);
	float newy = (z * vec.x) - (x * vec.z);
	float newz = (x * vec.y) - (y * vec.x);
	return vec4(newx, newy, newz);
}

// normalize a vector
void vec4::normalize() {
	float len = length();
	x /= len;
	y /= len;
	z /= len;
}

// clamps the values of the vector
void vec4::clamp(float low, float high) {
	if (x < low) {
		x = low;
	}
	if (y < low) {
		y = low;
	}
	if (z < low) {
		z = low;
	}
	if (x > high) {
		x = high;
	}
	if (y > high) {
		y = high;
	}
	if (z > high) {
		z = high;
	}
}

bool vec4::operator==(const vec4& v) {
	return x == v.x && y == v.y && z == v.z;
}

bool vec4::operator!=(const vec4& v) {
	return x != v.x || y != v.y || z != v.z;
}

bool vec4::operator<(const vec4& v) {
	return this->length() < v.length();
}

bool vec4::operator<=(const vec4& v) {
	return length() <= v.length();
}

bool vec4::operator>(const vec4& v) {
	return length() > v.length();
}

bool vec4::operator>=(const vec4& v) {
	return length() >= v.length();
}

vec4& vec4::operator=(const vec4& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

vec4& vec4::operator+=(const vec4& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

vec4& vec4::operator-=(const vec4& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

vec4& vec4::operator=(const float c) {
	x = c;
	y = c;
	z = c;
	w = 1.0f;
	return *this;
}

vec4& vec4::operator+=(const float c) {
	x += c;
	y += c;
	z += c;
	return *this;
}

vec4& vec4::operator-=(const float c) {
	x -= c;
	y -= c;
	z -= c;
	return *this;
}

vec4& vec4::operator*=(const float c) {
	x *= c;
	y *= c;
	z *= c;
	return *this;
}

vec4 operator-(const vec4& a, const vec4& b) {
	return vec4(a.x - b.x, a.y - b.y, a.z - b.z);
}

vec4 operator+(const vec4& a, const vec4& b) {
	return vec4(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec4 operator-(const vec4& a, const float c) {
	return vec4(a.x - c, a.y - c, a.z - c);
}

vec4 operator-(const float c, const vec4& a) {
	return vec4(a.x - c, a.y - c, a.z - c);
}

vec4 operator+(const vec4& a, const float c) {
	return vec4(a.x + c, a.y + c, a.z + c);
}

vec4 operator+(const float c, const vec4& a) {
	return vec4(a.x + c, a.y + c, a.z + c);
}

vec4 operator*(const vec4& a, const vec4& b) {
	return vec4(a.x * b.x, a.y * b.y, a.z * b.z);
}

vec4 operator*(const float c, const vec4& a) {
	return vec4(a.x * c, a.y * c, a.z * c);
}

vec4 operator*(const vec4& a, const float c) {
	return vec4(a.x * c, a.y * c, a.z * c);
}

// easily output a vector's information
std::ostream& operator<<(std::ostream& os, vec4& v) {
	os << v.x << ", " << v.y << ", " << v.z;
	return os;
}