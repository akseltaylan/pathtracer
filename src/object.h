#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>
#include <string>
#include "mesh.h"
#include "face.h"

class object {
	private:
		
	public:
		mesh obj_mesh;
		object();
		object(const char *);
		bool read_data(const char *);

};

#endif
