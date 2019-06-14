#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>
#include <string>
#include "mesh.h"
#include "face.h"

class Sphere
{
private:
	vec4 center;
	float radius;
public:
	Sphere(vec4 c, float r) : center(c), radius(r) {}
	// SETTERS
	void setCenter(vec4 c) { center = c; }
	void setRadius(float rad) { radius = rad; }

	// VIRTUAL FUNCTIONS

	// get vector from center of sphere to the point you're calculating normal of,
	// divide by the radius of the sphere to normalize the vector
	vec4 getNormal(vec4 p) {
		return vec4((p.x - center.x) / radius, (p.y - center.y) / radius, (p.z - center.z) / radius);
	}
	bool quadraticFormula(const float &a, const float &b, const float &c, float &t0, float &t1) {
		float discrem = (b * b) - (4 * a * c);
		//std::cout << discrem << std::endl;
		if (discrem < 0) {
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
	// will return two t values, eventually find the min positive
	bool intersect(ray& ray, float tNear) {
		float t0 = -1.0f;
		float t1 = -1.0f;
		std::vector<float> results;
		vec4 l = ray.p - center;
		vec4 ll = l;
		//std::cout << l.x << " " << l.y << " " << l.z << " L vector" << std::endl;
		vec4 dupv = ray.v;
		float a = ray.v.dot(dupv);
		float b = 2.0f * l.dot(ray.v);
		float c = l.dot(ll) - (radius * radius);
		//std::cout << a << " " << b << " " << c << " A B C" << std::endl;
		if (quadraticFormula(a, b, c, t0, t1)) {
			results.push_back(t0);
			results.push_back(t1);
		}
		else return false;

		if (results[0] < 0.0f && results[1] > 0.0f) {
			tNear = results[1];  
			return true;
		}
		else if (results[1] < 0 && results[0] > 0) {
			tNear = results[0];  
			return true;
		}
		else if (results[1] > 0 && results[0] > 0) {
			tNear = (results[1] < results[0]) ? results[1] : results[0]; 
			return true;
		}

		return false;
	}
};

class object {
	private:
		
	public:
		mesh obj_mesh;
		object();
		object(const char *);
		bool read_data(const char *);

};

#endif
