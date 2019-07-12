#ifndef IMPLANE_H
#define IMPLANE_H
#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <algorithm>

class implane {
	private:
		double width;
		double height;
		glm::vec3 center;
		int cur_x;
		int cur_y;
		
	public:
		implane();
		implane(int, int);
		glm::vec3 nextpixel(const int&, const int&, const int&);
		static const std::vector<float> jitter_matrix;
};

#endif