#include "mesh.h"

constexpr float k_epsilon = 1e-8;
static const float k_infinity = std::numeric_limits<float>::max();

bool mesh::get_data(const char * filepath) {

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
			glm::vec3 vertex(std::stof(vx), std::stof(vy), std::stof(vz));
			vertices.push_back(vertex);
		}
		else if (linetype == "vt") {
			std::string uu, vv;
			ss >> uu >> vv;
			vec2 uv(std::stof(uu), std::stof(vv));
			uvs.push_back(uv);
		}
		else if (linetype == "vn") {
			std::string nx, ny, nz;
			ss >> nx >> ny >> nz;
			glm::vec3 normal(std::stof(nx), std::stof(ny), std::stof(nz));
			normals.push_back(normal);
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
				v_idxs.push_back(pIdx - 1);
				fuvs.push_back(vIdx - 1);
				uv_idxs.push_back(vIdx - 1);
				fnormals.push_back(nIdx - 1);
				n_idxs.push_back(nIdx - 1);
				ss >> fstr;
			}
			face f(fpts, fuvs, fnormals);
			f.set_normal(vertices, false);
			faces.push_back(f);
			++num_tris;
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

mesh::mesh(const char * filepath) {
	vertices = std::vector<glm::vec3>();
	uvs = std::vector<vec2>();
	normals = std::vector<glm::vec3>();
	v_idxs = std::vector<int>();
	uv_idxs = std::vector<int>();
	n_idxs = std::vector<int>();
	faces = std::vector<face>();
	num_tris = 0;
	get_data(filepath);
}

void mesh::debug() {
	std::cout << "total vertex count: " << vertices.size() << std::endl;
	std::cout << "total faces count: " << faces.size() << std::endl;
}

bool mesh::rayTriangleIntersect(const ray& r, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float &t, const int& j) const {

	// compute triangle's normal 

	glm::vec3 A = v1 - v0;
	glm::vec3 B = v2 - v0;
	glm::vec3 pvec = glm::cross(r.v, B);
	float det = glm::dot(A, pvec);

	// ray and triangle are parallel if det is close to 0
	if (fabs(det) < k_epsilon) return false;

	float inv_det = 1 / det;
	glm::vec3 tvec = r.p - v0;
	float u = glm::dot(tvec,pvec) * inv_det;
	if (u < 0 || u > 1) return false;

	// test if ray and triangle are parallel - if so, fails, RETURN false
	/*
	float denom = glm::dot(f.normal,r.v);
	if (denom == 0) return false;*/

	glm::vec3 qvec = glm::cross(tvec,A);
	float v = glm::dot(r.v,qvec) * inv_det;
	if (v < 0 || u + v > 1) return false;

	t = glm::dot(B,qvec) * inv_det;
	return true;
	// compute t, from which we compute the intersection point
	/*
	float D = glm::dot(f.normal,f.v1);
	float numer = glm::dot(f.normal, r.p) + D;
	t = numer / denom;
	if (t < 0) return false;*/

	// test if P is on the left side of each one of the triangle's edges
	//glm::vec3 phit = r.p + r.v * t;

	// if inside out-test succeeds, RETURN true
	/*
	glm::vec3 edge_0 = vertices[f.pts[1]] - vertices[f.pts[0]];
	glm::vec3 edge_1 = vertices[f.pts[2]] - vertices[f.pts[1]];
	glm::vec3 edge_2 = vertices[f.pts[0]] - vertices[f.pts[2]];
	glm::vec3 c0 = phit - vertices[f.pts[0]];
	glm::vec3 c1 = phit - vertices[f.pts[1]];
	glm::vec3 c2 = phit - vertices[f.pts[2]];
	if (
		glm::dot(f.normal,glm::cross(edge_0,c0)) > 0 &&
		glm::dot(f.normal, glm::cross(edge_1, c1)) > 0 &&
		glm::dot(f.normal, glm::cross(edge_2, c2)) > 0) return true;
	
	return false;*/
}

bool mesh::intersect(const ray& r, float& tNear) const {
	bool intersection = false;
	auto start = std::chrono::high_resolution_clock::now();
	int j = 0;
	for (int i = 0; i < faces.size() - 2; ++i) {
		const glm::vec3& v0 = vertices[v_idxs[j]];
		const glm::vec3& v1 = vertices[v_idxs[j + 1]];
		const glm::vec3& v2 = vertices[v_idxs[j + 2]];
		float t = k_infinity;
		if (rayTriangleIntersect(r, v0,v1,v2, t, j) && t < tNear) {
			tNear = t;
			intersection |= true;
		}
		j += 3;
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<double, std::milli>(stop - start).count();
	if (DEBUG) std::cout << "Checked all triangles in object for intersections in " << duration/1000 << " seconds" << std::endl;

	return intersection;
}

void mesh::compute_bounds(glm::vec3 plane_set_normal, std::vector<float>& ds) const {
	float d_near = k_infinity;
	float d_far = -k_infinity;
	for (int i = 0; i < vertices.size(); ++i) {
		float D = plane_set_normal.x * vertices[i].x + plane_set_normal.y * vertices[i].y + plane_set_normal.z * vertices[i].z;
		d_near = std::min(d_near, D);
		d_far = std::max(d_far, D);
	}
	ds[0] = d_near;
	ds[1] = d_far;
}

