#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "object.h"

class scene {
private:
	std::vector<object *> objs;
	//TODO: lights will also be in here
public:
	scene();
	~scene();
	void add_obj(object *);
	std::vector<object *> get_objs();
};

#endif