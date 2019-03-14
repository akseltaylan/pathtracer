#include "vec4.h"
#include "vec2.h"
#include "mat4.h"
#include "image.h"
#include "pathtracer.h"
#include <iostream>

/*
	Currently main is just being
	used to test things.
*/

int main() {

	/* MATH TESTS
	vec4 v1(2, 4, 3);
	vec4 v2(1, 1, 2);
	vec4 v4(2, 1, 3);
	vec4 v3 = v1.cross(v2);
	std::cout << v1.dot(v2) << " is the dot product" << std::endl;
	std::cout << v3 << " is the cross product" << std::endl;
	bool test = v1 != v4;
	std::cout << test << " are they equal" << std::endl; 
	*/

	image * img = new image(800,600);
	pathtracer renderer(img);

	renderer.render();

	return 0;
}