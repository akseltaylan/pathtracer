#include "object.h"

object::object() {

}

object::object(const char * filepath) {
	obj_mesh = mesh();
	read_data(filepath);
}

bool object::read_data(const char * filepath) {

	// read in file
	FILE * file = fopen(filepath, "r");
	
	if (file == NULL) {
		perror(NULL);
		std::cerr << "Unable to open file!" << std::endl;
		return false;
	}

	std::vector< unsigned int > v_indices, uv_indices, normal_indices;

	// parse obj data

	int count = 1;
	char line[128];
	while (fgets(line, sizeof(line), file)) {
		std::stringstream ss;
		ss << line;
		std::string linetype;
		ss >> linetype;
		if (linetype == "v") {
			std::string vx, vy, vz;
			ss >> vx >> vy >> vz;
			vec4 vertex(std::stof(vx),std::stof(vy),std::stof(vz));
			obj_mesh.vertices.push_back(vertex);
		}
		else if (linetype == "vt") {
			std::string uu, vv;
			ss >> uu >> vv;
			vec2 uv(std::stof(uu), std::stof(vv));
			obj_mesh.uvs.push_back(uv);
		}
		else if (linetype == "vn") {
			std::string nx, ny, nz;
			ss >> nx >> ny >> nz;
			vec4 normal(std::stof(nx), std::stof(ny), std::stof(nz));
			obj_mesh.normals.push_back(normal);
		}
		else if (linetype == "f") {
			std::vector<int> fpts;
			std::vector<int> fuvs;
			std::vector<int> fnormals;
			std::string fstr;
			ss >> fstr;

			while (!ss.eof()) {
				int pIdx, vIdx, nIdx;
				sscanf(fstr.c_str(), "%d/%d/%d", &pIdx, &vIdx, &nIdx);
				fpts.push_back(pIdx - 1);
				fuvs.push_back(vIdx - 1);
				fnormals.push_back(nIdx - 1);
				ss >> fstr;
			}

			face f(fpts, fuvs, fnormals);
			obj_mesh.faces.push_back(f);
		}
		
		++count;
	}

	fclose(file);

	return true;
}
 
