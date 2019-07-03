#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "vec2.h"
#include "mat4.h"
#include "image.h"
#include "scene.h"
#include "mesh.h"
#include "pathtracer.h"
#include <iostream>

/*
	Currently main is just being
	used to test things.
*/

void debug_scene(scene * s, pathtracer pt) {
	std::cout << "Number of objects: " << s->get_objs().size() << std::endl;
	std::cout << "Number of primary rays: " << pt.num_rays << std::endl;
}

int main() {
	
	const char * filepath = ".\\..\\src\\objs\\bunny.obj";
	
	mesh * obj = new mesh(filepath);

	std::cout << "Number of triangles: " << obj->num_tris << std::endl;
	
	for (int i = 0; i < obj->vertices.size(); ++i) {
		obj->vertices[i] *= 1000;
	}

	scene * test = new scene();
	test->add_obj(obj);
	
	image * img = new image(640,480);

	pathtracer renderer(img);
	renderer.set_scene(test);

	renderer.render();

	debug_scene(test, renderer);

	return 0;
}