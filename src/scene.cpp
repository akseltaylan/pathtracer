#include "scene.h"

scene::scene() {
	bg_color = glm::vec3(0.0f);
}

scene::~scene() {
	for (object * obj : objs) {
		free(obj);
	}
}

void scene::add_obj(object * obj) {
	objs.push_back(obj);
}

void scene::add_light(light * l) {
	lights.push_back(l);
}

std::vector<object *> scene::get_objs() {
	return objs;
}

std::vector<light *> scene::get_lights() {
	return lights;
}

glm::vec3 scene::get_camera() {
	return camera;
}

void scene::bunny_setup() {

	// create bunny
	const char * filepath = ".\\..\\src\\objs\\bunny.obj";	
	mesh * bunny = new mesh(filepath);
	for (int i = 0; i < bunny->vertices.size(); ++i) {
		bunny->vertices[i] *= 1000.0f;
	}
	bunny->set_albedo(glm::vec3(0.0f, 0.0f, 0.7f));
	bunny->set_material(new material(0.05f, 0.95f, 0.1f, 16.0f));
	add_obj(bunny);
	
	// floor
	filepath = ".\\..\\src\\objs\\plane.obj";
	mesh * plane = new mesh(filepath);
	for (int i = 0; i < plane->vertices.size(); ++i) {
		plane->vertices[i] *= 100.0f;

	}
	plane->set_albedo(glm::vec3(0.9f, 0.9f, 0.9f));
	plane->set_material(new material(0.1f, 0.8f, 0.2f, 1.0f));
	add_obj(plane);

	// create light
	point_light * pl1 = new point_light(glm::vec3(0.0f, 400.0f, 250.0f), 0.9f, glm::vec3(1.0f));
	add_light(pl1);

	// set camera pos
	camera = glm::vec3(0.0f, 0.0f, 1000.0f);

	// set bg color
	bg_color = glm::vec3(164.0f / 255.0f, 198.0f / 255.0f, 252.0f / 255.0f);
}

void scene::sphere_setup() {

	// create sphere
	const char * filepath = ".\\..\\src\\objs\\sphere.obj";
	mesh * sphere = new mesh(filepath);
	sphere->set_albedo(glm::vec3(0.0f, 1.0f, 0.0f));
	sphere->set_material(new material(0.05f, 0.95f, 0.35f, 32.0f));
	add_obj(sphere);

	// floor
	filepath = ".\\..\\src\\objs\\plane.obj";
	mesh * plane = new mesh(filepath);

	for (int i = 0; i < plane->vertices.size(); ++i) {
		plane->vertices[i] *= 100;

	}
	plane->set_albedo(glm::vec3(0.9f, 0.9f, 0.9f));
	plane->set_material(new material(0.1f, 0.8f, 0.0f, 1.0f));
	add_obj(plane);

	// create light
	point_light * pl1 = new point_light(glm::vec3(-2.0f, 2.0f, 21.0f), 0.9f, glm::vec3(1.0f));
	add_light(pl1);

	// set camera pos
	camera = glm::vec3(0.0f, 0.0f, 21.0f);

	// set bg color
	bg_color = glm::vec3(0.0f);
}

void scene::gl_test_setup() {
	// create sphere
	const char * filepath = ".\\..\\src\\objs\\sphere.obj";
	mesh * sphere = new mesh(filepath);
	for (int i = 0; i < sphere->vertices.size(); ++i) {
		sphere->vertices[i] *= 2.0f;
	}
	sphere->set_albedo(glm::vec3(0.0f, 1.0f, 0.0f));
	sphere->set_material(new material(0.05f, 0.95f, 0.35f, 32.0f));
	add_obj(sphere);

	mesh * sphere2 = new mesh(filepath);
	for (int i = 0; i < sphere2->vertices.size(); ++i) {
		sphere2->vertices[i] *= 2.0f;
		sphere2->vertices[i].x -= 80.0f;
	}
	sphere2->set_albedo(glm::vec3(1.0f, 0.0f, 0.0f));
	sphere2->set_material(new material(0.05f, 0.95f, 0.35f, 32.0f));
	add_obj(sphere2);

	// floor
	filepath = ".\\..\\src\\objs\\plane.obj";
	mesh * plane = new mesh(filepath);
	for (int i = 0; i < plane->vertices.size(); ++i) {
		plane->vertices[i] *= 100.0f;

	}
	plane->set_albedo(glm::vec3(0.9f, 0.9f, 0.9f));
	plane->set_material(new material(0.1f, 0.8f, 0.2f, 1.0f));
	add_obj(plane);

	// create light
	point_light * pl1 = new point_light(glm::vec3(0.0f, 400.0f, 250.0f), 0.9f, glm::vec3(1.0f));
	add_light(pl1);

	// set camera pos
	camera = glm::vec3(0.0f, 0.0f, 1000.0f);

	// set bg color
	bg_color = glm::vec3(0.5f);
}