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
#include <iostream>

/*
	Currently main is just being
	used to test things.
*/

void debug_scene(scene * s, const pathtracer& pt, const int& total_tris) {
	std::cout << "Number of objects: " << s->get_objs().size() << std::endl;
	std::cout << "Total tris: " << total_tris << std::endl;
	std::cout << "Number of primary rays: " << pt.num_rays << std::endl;
}

int main() {
	
	const char * bunny_filepath = ".\\..\\src\\objs\\bunny.obj";
	const char * sphere_filepath = ".\\..\\src\\objs\\sphere.obj";
	
	mesh * bunny = new mesh(bunny_filepath);
	mesh * sphere = new mesh(sphere_filepath);
	
	for (int i = 0; i < bunny->vertices.size(); ++i) {
		bunny->vertices[i] *= 1000;
	}

	int total_tris = 0;

	scene * test = new scene();
	test->add_obj(bunny);
	total_tris += bunny->num_tris;
	
	image * img = new image(640,480);

	pathtracer renderer(img);
	renderer.set_scene(test);

	renderer.render();

	debug_scene(test, renderer, total_tris);

	return 0;
}