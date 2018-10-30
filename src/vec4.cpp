#include "vec4.h"

// empty constructor
vec4::vec4() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 1.0;
}

// initialize entire vector with one value
vec4::vec4(double a) {
	x = a;
	y = a;
	z = a;
	w = a;
}

// basic constructor
vec4::vec4(double xx, double yy, double zz) {
	x = xx;
	y = yy;
	z = zz;
	w = 1.0;
}

// includes w value
vec4::vec4(double xx, double yy, double zz, double ww) {
	// check if w can divide the other values
	if (ww != 0) {
		x = xx / ww;
		y = yy / ww;
		z = zz / ww;
		w = 1.0;
	}
	else {
		x = xx;
		y = yy;
		z = zz;
		w = ww;
	}
}

// magnitude of vector
double vec4::length() {
	return sqrt((x*x) + (y*y) + (z*z));
}

// dot product of vector
double vec4::dot(vec4& vec) {
	return (x * vec.x) + (y * vec.y) + (z * vec.z);
}

// cross product of vector
vec4 vec4::cross(vec4& vec) {
	double newx = (y * vec.z) - (z * vec.y);
	double newy = (z * vec.x) - (x * vec.z);
	double newz = (x * vec.y) - (y * vec.x);
	return vec4(newx, newy, newz);
}

// normalize a vector
void vec4::normalize() {
	double len = length();
	x /= len;
	y /= len;
	z /= len;
}

// clamps the values of the vector
void vec4::clamp(double low, double high) {
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

// easily output a vector's information
std::ostream& operator<<(std::ostream& os, vec4& v) {
	os << v.x << ", " << v.y << ", " << v.z;
	return os;
}