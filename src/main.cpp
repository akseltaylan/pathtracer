#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "math/vec2.h"
#include "math/mat4.h"
#include "image.h"
#include "scene.h"
#include "geo/mesh.h"
#include "pathtracer.h"
#include "look/point_light.h"
#include <iostream>

void debug_scene(scene * s, const pathtracer& pt) {
	std::cout << "Number of objects: " << s->get_objs().size() << std::endl;
	std::cout << "Number of primary rays: " << pt.num_rays << std::endl;
}

int main() {

	scene * test = new scene();
	test->gl_test_setup();

	image * img = new image(640,480);

	pathtracer renderer(img);
	renderer.set_scene(test);

	renderer.render();

	if (DEBUG) debug_scene(test, renderer);

	return 0;
}