#include "vec4.h"
#include <iostream>

/*
	Currently main is just being
	used to test things.
*/

int main() {
	vec4 v1(2, 4, 3);
	vec4 v2(1, 1, 2);
	vec4 v3 = v1.cross(v2);
	std::cout << v1.dot(v2) << " is the dot product" << std::endl;
	std::cout << v3 << " is the cross product" << std::endl;
	return 0;
}