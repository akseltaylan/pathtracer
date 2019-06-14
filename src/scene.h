#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "object.h"

class scene {
private:
	std::vector<Sphere *> objs;
	//TODO: lights will also be in here
public:
	scene();
	~scene();
	void add_obj(Sphere *);
	std::vector<Sphere *> get_objs();
};

#endif