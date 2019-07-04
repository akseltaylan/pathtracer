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

class object {
	private:
		
	public:
		object();
		virtual ~object();
		virtual bool intersect(const ray&, float&) const = 0;
		virtual void compute_bounds(glm::vec3, std::vector<float> &) const = 0;
};

#endif
