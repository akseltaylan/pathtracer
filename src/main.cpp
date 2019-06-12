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
#include "mesh.h"
#include "pathtracer.h"
#include <iostream>

/*
	Currently main is just being
	used to test things.
*/

int main() {
	
	const char * filepath = ".\\..\\src\\objs\\bunny.obj";
	object bunny(filepath);

	bunny.obj_mesh.debug();
	
	image * img = new image(800,600);
	pathtracer renderer(img);
	
	renderer.render();	

	return 0;
}