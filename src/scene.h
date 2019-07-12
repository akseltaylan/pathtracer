#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "geo/object.h"
#include "geo/mesh.h"
#include "look/light.h"
#include "look/point_light.h"

class scene {
private:
	std::vector<object *> objs;
	std::vector<light *> lights;
	glm::vec3 camera;
public:
	glm::vec3 bg_color;

	scene();
	~scene();
	void add_obj(object *);
	void add_light(light *);
	std::vector<object *> get_objs();
	std::vector<light *> get_lights();
	glm::vec3 get_camera();
	
	// example scene set ups
	void bunny_setup();
	void sphere_setup();
	void gl_test_setup();
};

#endif