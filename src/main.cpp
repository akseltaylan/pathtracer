#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "vec4.h"
#include "vec2.h"
#include "mat4.h"
#include "image.h"
#include "object.h"
#include "scene.h"
#include "mesh.h"
#include "pathtracer.h"
#include <iostream>

/*
	Currently main is just being
	used to test things.
*/

int main() {
	
	const char * filepath = ".\\..\\src\\objs\\bunny.obj";
	object * bunny = new object(filepath);
	Sphere * sphere = new Sphere(vec4(0.0f, -1.0f, 200.0f), 50.0f);

	scene * test = new scene();
	//test->add_obj(bunny);
	test->add_obj(sphere);
	
	image * img = new image(800,600);
	pathtracer renderer(img);
	renderer.set_scene(test);
	
	renderer.render();	

	return 0;
}