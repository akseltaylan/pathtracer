#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>
#include <string>
#include "../ray.h"
#include "face.h"
#include "../look/material.h"

class object {
	private:
		glm::vec3 albedo; // base color of object
		material * mat;
	public:
		glm::mat4 transform = glm::mat4(1.0f);
		glm::mat4 inv_transform = glm::inverse(transform);
		bool is_light = false;

		object();
		virtual ~object();
		glm::vec3 get_albedo() const;
		material * get_material() const;
		void set_albedo(glm::vec3);
		void set_material(material *);
		virtual bool intersect(const ray&, float&, int&, float&, float&) const = 0;
		virtual void compute_bounds(glm::vec3, std::vector<float> &) const = 0;
		virtual void get_shading_properties(glm::vec3&, glm::vec3&, const float&, const float&, const float&, const int&, const ray&, glm::vec2&) const = 0;
};

#endif
