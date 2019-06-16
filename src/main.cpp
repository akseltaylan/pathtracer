#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "vec2.h"
#include "mat4.h"
#include "image.h"
#include "object.h"
#include "scene.h"
#include "mesh.h"
#include <chrono>
#include "pathtracer.h"
#include <iostream>

/*
	Currently main is just being
	used to test things.
*/

void debug_scene(scene * s, pathtracer pt) {
	std::cout << "Number of objects: " << s->get_objs().size() << std::endl;
	int facect = 0;
	for (object * obj : s->get_objs()) {
		facect += obj->obj_mesh.faces.size();
	}
	std::cout << "Number of faces: " << facect << std::endl;
	std::cout << "Number of primary rays: " << pt.num_rays << std::endl;
}

int main() {
	
	const char * filepath = ".\\..\\src\\objs\\sphere.obj";

	auto start = std::chrono::high_resolution_clock::now();
	object * sphere = new object(filepath);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast< std::chrono::microseconds >(stop - start);
	if (DEBUG) std::cout << "Read in object files in " << duration.count() * 1e-6 << " seconds" << std::endl;
	scene * test = new scene();
	test->add_obj(sphere);
	
	image * img = new image(640,480);
	pathtracer renderer(img);
	renderer.set_scene(test);
	debug_scene(test, renderer);
	
	renderer.render();	
	
	return 0;
}