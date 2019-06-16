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
			glm::vec3 vertex(std::stof(vx),std::stof(vy),std::stof(vz));
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
			glm::vec3 normal(std::stof(nx), std::stof(ny), std::stof(nz));
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
			f.set_normal(obj_mesh.vertices, false);
			obj_mesh.faces.push_back(f);
			/*
			else if (fpts.size() == 4) {
				float dist1 = glm::distance(obj_mesh.vertices[fpts[0]], obj_mesh.vertices[fpts[1]]);
				float dist2 = glm::distance(obj_mesh.vertices[fpts[2]], obj_mesh.vertices[fpts[3]]);
				if (dist1 > dist2) {
					std::vector<int> fpt1 = { fpts[0],fpts[2],fpts[3] };
					std::vector<int> fpt2 = { fpts[2],fpts[1],fpts[3] };
					std::vector<int> fuv1 = { fuvs[0],fuvs[2],fuvs[3] };
					std::vector<int> fuv2 = { fuvs[2],fuvs[1],fuvs[3] };
					std::vector<int> fnm1 = { fnormals[0],fnormals[2],fnormals[3] };
					std::vector<int> fnm2 = { fnormals[2],fnormals[1],fnormals[3] };
					obj_mesh.faces.push_back(face(fpt1, fuv1, fnm1));
					obj_mesh.faces.push_back(face(fpt2,fuv2,fnm2));
				}
				else {
					std::vector<int> fpt1 = { fpts[0],fpts[2],fpts[1] };
					std::vector<int> fpt2 = { fpts[0],fpts[1],fpts[3] };
					std::vector<int> fuv1 = { fuvs[0],fuvs[2],fuvs[1] };
					std::vector<int> fuv2 = { fuvs[0],fuvs[1],fuvs[3] };
					std::vector<int> fnm1 = { fnormals[0],fnormals[2],fnormals[1] };
					std::vector<int> fnm2 = { fnormals[0],fnormals[1],fnormals[3] };
					obj_mesh.faces.push_back(face(fpt1, fuv1, fnm1));
					obj_mesh.faces.push_back(face(fpt2, fuv2, fnm2));
				}
			}*/
		}
		
		++count;
	}

	fclose(file);

	return true;
}
 
