#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "geo/object.h"
#include "look/light.h"

class scene {
private:
	std::vector<object *> objs;
	std::vector<light *> lights;
public:
	scene();
	~scene();
	void add_obj(object *);
	void add_light(light *);
	std::vector<object *> get_objs();
	std::vector<light *> get_lights();
};

#endif