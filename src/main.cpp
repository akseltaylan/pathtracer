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

	point_light * pl1 = new point_light(glm::vec3(0.0f, 250.0f, 300.0f));
	pl1->set_intensity(glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.5, 0.5f, 0.5f), glm::vec3(0.2f, 0.2f, 0.2f));
	
	for (int i = 0; i < bunny->vertices.size(); ++i) {
		bunny->vertices[i] *= 1000;
	}
	bunny->set_albedo(glm::vec3(0.0f, 1.0f, 0.0f));
	bunny->set_material(new material(0.7f, 0.7f, 0.2f, 0.01f));
	sphere->set_albedo(glm::vec3(0.0f, 1.0f, 0.0f));
	sphere->set_material(new material(0.7f, 0.7f, 0.2f, 0.01f));

	int total_tris = 0;

	scene * test = new scene();
	test->add_obj(bunny);
	total_tris += bunny->num_tris;
	test->add_light(pl1);
	
	image * img = new image(640,480);

	pathtracer renderer(img);
	renderer.set_scene(test);

	renderer.render();

	debug_scene(test, renderer, total_tris);

	return 0;
}