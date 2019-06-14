#include "scene.h"

scene::scene() {

}

scene::~scene() {
	for (Sphere * obj : objs) {
		free(obj);
	}
}

void scene::add_obj(Sphere * obj) {
	objs.push_back(obj);
}

std::vector<Sphere *> scene::get_objs() {
	return objs;
}