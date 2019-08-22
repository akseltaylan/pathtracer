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

void scene::gl_sphere_setup() {
	// create sphere
	
	const char * filepath = ".\\..\\src\\objs\\sphere.obj";
	
	mesh * sphere = new mesh(filepath);
	for (int i = 0; i < sphere->vertices.size(); ++i) {
		sphere->vertices[i] *= 4.0f;
		sphere->vertices[i].y -= 100.0f;
		sphere->vertices[i].x += 90.0f;
		sphere->vertices[i].z -= 50.0f;
	}
	sphere->set_albedo(glm::vec3(0.9f));
	sphere->set_material(new material(0.7f, 0.95f, 0.35f, 32.0f, glm::vec3(1.0f)*.999f, glm::vec3(0.0f), material::mat_type::specular));
	add_obj(sphere);

	
	mesh * sphere2 = new mesh(filepath);
	for (int i = 0; i < sphere2->vertices.size(); ++i) {
		sphere2->vertices[i] *= 4.0f;
		sphere2->vertices[i].x -= 200.0f;
		sphere2->vertices[i].y -= 80.0f;
		sphere2->vertices[i].z -= 100.0f;
	}
	sphere2->set_albedo(glm::vec3(0.9f));
	sphere2->set_material(new material(0.7f, 0.95f, 0.35f, 32.0f, glm::vec3(1.0f)*.999f, glm::vec3(0.0f), material::mat_type::glass));
	add_obj(sphere2);
	
	// floor
	
	filepath = ".\\..\\src\\objs\\plane.obj";
	mesh * plane = new mesh(filepath);
	for (int i = 0; i < plane->vertices.size(); ++i) {
		plane->vertices[i] *= 100.0f;

	}
	plane->set_albedo(glm::vec3(0.9f));
	plane->set_material(new material(0.7f, 1.0f, 0.2f, 1.0f, glm::vec3(0.9f)));
	add_obj(plane);

	//ceiling

	filepath = ".\\..\\src\\objs\\plane.obj";
	mesh * ceil = new mesh(filepath);
	for (int i = 0; i < ceil->vertices.size(); ++i) {
		ceil->vertices[i] *= 100.0f;
		ceil->vertices[i].y += 400.0f;

	}
	ceil->set_albedo(glm::vec3(0.9f));
	ceil->set_material(new material(0.7f, 1.0f, 0.2f, 1.0f, glm::vec3(0.9f)));
	add_obj(ceil);

	filepath = ".\\..\\src\\objs\\back.obj";
	mesh * plane2 = new mesh(filepath);
	for (int i = 0; i < plane2->vertices.size(); ++i) {
		plane2->vertices[i] *= 1.0f;

	}
	plane2->set_albedo(glm::vec3(0.9f));
	plane2->set_material(new material(0.7f, 1.0f, 0.2f, 1.0f, glm::vec3(0.9f)));
	add_obj(plane2);
	
	filepath = ".\\..\\src\\objs\\left_wall.obj";
	mesh * left_wall = new mesh(filepath);
	for (int i = 0; i < left_wall->vertices.size(); ++i) {
		left_wall->vertices[i] *= 100.0f;

	}
	left_wall->set_albedo(glm::vec3(1.0f, 0.0f, 0.0f));
	left_wall->set_material(new material(0.7f, 1.0f, 0.2f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
	add_obj(left_wall);

	filepath = ".\\..\\src\\objs\\right_wall.obj";
	mesh * right_wall = new mesh(filepath);
	for (int i = 0; i < right_wall->vertices.size(); ++i) {
		right_wall->vertices[i] *= 100.0f;

	}
	right_wall->set_albedo(glm::vec3(0.0f, 1.0f, 0.0f));
	right_wall->set_material(new material(0.7f, 1.0f, 0.2f, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	add_obj(right_wall);
	
	// create light
	
	//point_light * pl1 = new point_light(glm::vec3(0.0f, 600.0f, 250.0f), 0.9f, glm::vec3(1.0f));
	//add_light(pl1);
	
	
	area_light * al1 = new area_light(glm::vec3(0.0f, 600.0f, 250.0f), 0.9f, glm::vec3(1.0f));
	al1->area = new mesh(".\\..\\src\\objs\\plane.obj");
	for (int i = 0; i < al1->area->vertices.size(); ++i) {
		al1->area->vertices[i] *= 10.0f;
		al1->area->vertices[i].y += 200.0f;
		
	}
	al1->area->set_material(new material(0.7f, 0.95f, 0.35f, 32.0f, glm::vec3(1.0f), glm::vec3(12.0f), material::mat_type::diffuse));
	al1->area->set_albedo(al1->get_color());
	al1->area->is_light = true;
	add_obj(al1->area);
	add_light(al1);
	

	// set camera pos
	camera = glm::vec3(0.0f, 0.0f, 1000.0f);

	// set bg color
	bg_color = glm::vec3(0.0f);
}

void scene::gl_bunny_setup() {
	// create sphere

	const char * filepath = ".\\..\\src\\objs\\sphere.obj";

	mesh * sphere = new mesh(filepath);
	for (int i = 0; i < sphere->vertices.size(); ++i) {
		sphere->vertices[i] *= 4.0f;
		sphere->vertices[i].y -= 100.0f;
		sphere->vertices[i].x += 90.0f;
		sphere->vertices[i].z -= 100.0f;
	}
	sphere->set_albedo(glm::vec3(0.9f));
	sphere->set_material(new material(0.7f, 0.95f, 0.35f, 32.0f, glm::vec3(0.0f,0.0f,0.9f), glm::vec3(0.0f), material::mat_type::diffuse));
	sphere->get_material()->set_texture(new texture(".\\..\\src\\textures\\bricks.ppm"));
	add_obj(sphere);


	// create bunny
	filepath = ".\\..\\src\\objs\\bunny.obj";
	mesh * bunny = new mesh(filepath);
	for (int i = 0; i < bunny->vertices.size(); ++i) {
		bunny->vertices[i] *= 1000.0f;
		bunny->vertices[i].y -= 200.0f;
		bunny->vertices[i].x -= 90.0f;
		//bunny->vertices[i].z -= 100.0f;
	}
	bunny->set_albedo(glm::vec3(0.0f, 0.0f, 0.7f));
	bunny->set_material(new material(0.7f, 0.95f, 0.35f, 32.0f, glm::vec3(1.0f), glm::vec3(0.0f), material::mat_type::specular));
	add_obj(bunny);

	// floor

	filepath = ".\\..\\src\\objs\\plane.obj";
	mesh * plane = new mesh(filepath);
	for (int i = 0; i < plane->vertices.size(); ++i) {
		plane->vertices[i] *= 100.0f;

	}
	plane->set_albedo(glm::vec3(0.9f));
	plane->set_material(new material(0.7f, 1.0f, 0.2f, 1.0f, glm::vec3(0.9f)));
	//plane->get_material()->set_texture(new texture(".\\..\\src\\textures\\bricks.ppm"));
	add_obj(plane);

	//ceiling

	filepath = ".\\..\\src\\objs\\plane.obj";
	mesh * ceil = new mesh(filepath);
	for (int i = 0; i < ceil->vertices.size(); ++i) {
		ceil->vertices[i] *= 100.0f;
		ceil->vertices[i].y += 400.0f;

	}
	ceil->set_albedo(glm::vec3(0.9f));
	ceil->set_material(new material(0.7f, 1.0f, 0.2f, 1.0f, glm::vec3(0.9f)));
	add_obj(ceil);

	filepath = ".\\..\\src\\objs\\back.obj";
	mesh * plane2 = new mesh(filepath);
	for (int i = 0; i < plane2->vertices.size(); ++i) {
		plane2->vertices[i] *= 1.0f;

	}
	plane2->set_albedo(glm::vec3(0.9f));
	plane2->set_material(new material(0.7f, 1.0f, 0.2f, 1.0f, glm::vec3(0.9f)));
	add_obj(plane2);

	filepath = ".\\..\\src\\objs\\left_wall.obj";
	mesh * left_wall = new mesh(filepath);
	for (int i = 0; i < left_wall->vertices.size(); ++i) {
		left_wall->vertices[i] *= 100.0f;

	}
	left_wall->set_albedo(glm::vec3(1.0f, 0.0f, 0.0f));
	left_wall->set_material(new material(0.7f, 1.0f, 0.2f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
	add_obj(left_wall);

	filepath = ".\\..\\src\\objs\\right_wall.obj";
	mesh * right_wall = new mesh(filepath);
	for (int i = 0; i < right_wall->vertices.size(); ++i) {
		right_wall->vertices[i] *= 100.0f;

	}
	right_wall->set_albedo(glm::vec3(0.0f, 1.0f, 0.0f));
	right_wall->set_material(new material(0.7f, 1.0f, 0.2f, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	add_obj(right_wall);

	// create light

	//point_light * pl1 = new point_light(glm::vec3(0.0f, 600.0f, 250.0f), 0.9f, glm::vec3(1.0f));
	//add_light(pl1);


	area_light * al1 = new area_light(glm::vec3(0.0f, 600.0f, 250.0f), 0.9f, glm::vec3(1.0f));
	al1->area = new mesh(".\\..\\src\\objs\\plane.obj");
	for (int i = 0; i < al1->area->vertices.size(); ++i) {
		al1->area->vertices[i] *= 10.0f;
		al1->area->vertices[i].y += 200.0f;
		al1->area->vertices[i].z += 100.0f;

	}
	al1->area->set_material(new material(0.7f, 0.95f, 0.35f, 32.0f, glm::vec3(1.0f), glm::vec3(12.0f), material::mat_type::diffuse));
	al1->area->set_albedo(al1->get_color());
	al1->area->is_light = true;
	add_obj(al1->area);
	add_light(al1);


	// set camera pos
	camera = glm::vec3(0.0f, 0.0f, 1000.0f);

	// set bg color
	bg_color = glm::vec3(0.0f);
}