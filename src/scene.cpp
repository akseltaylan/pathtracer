#include "scene.h"

scene::scene() {

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