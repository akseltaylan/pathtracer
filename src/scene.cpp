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

std::vector<object *> scene::get_objs() {
	return objs;
}