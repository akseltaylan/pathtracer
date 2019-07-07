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
				int pIdx, vIdx, nIdx = 0;
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
			faces.push_back(f);
			++num_tris;
		}

		++count;
	}

	fclose(file);

	if (DEBUG) debug(filepath);

	return true;
}

void mesh::populate_normals() {
	if (normals.size() == 0) {
		normals = std::vector<glm::vec3>(vertices.size(), glm::vec3(0.0f));
		for (auto& f : faces) {
			f.set_normal(vertices, true);
			normals[f.pts[0]] += f.normal;
			normals[f.pts[1]] += f.normal;
			normals[f.pts[2]] += f.normal;
		}
	}
}

void mesh::set_to_origin() {
	
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1000), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 model = transform;
	glm::mat4 mvp = projection * view * model;

	/*
	for (int i = 0; i < vertices.size(); ++i) {
		glm::vec4 pt = glm::vec4(vertices[i], 1.0f);
		pt = glm::mat4(1.0f) * pt;
		vertices[i] = glm::vec3(pt.x, pt.y, pt.z);
	}*/
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
	populate_normals();
	set_to_origin();

}

void mesh::debug(const char * filepath) {
	std::cout << "Geo data for " << filepath << ": " << std::endl;
	std::cout << "Total vertex count: " << vertices.size() << std::endl;
	std::cout << "Total faces count: " << faces.size() << std::endl;
	std::cout << "Total normals count: " << normals.size() << std::endl;
	std::cout << "---" << std::endl;
}

bool mesh::ray_triangle_intersect(const ray& r, const glm::vec3& v0, const glm::vec3& v1,
								  const glm::vec3& v2, float &t, float& u, float& v) const {

	// compute triangle's normal 
	glm::vec3 A = v1 - v0;
	glm::vec3 B = v2 - v0;
	
	glm::vec3 pvec = glm::cross(r.v, B);
	float det = glm::dot(A, pvec);

	// ray and triangle are parallel if det is close to 0
	if (fabs(det) < k_epsilon) return false;

	float inv_det = 1 / det;
	glm::vec3 tvec = r.p - v0;
	u = glm::dot(tvec,pvec) * inv_det;
	if (u < 0 || u > 1) return false;

	glm::vec3 qvec = glm::cross(tvec,A);
	v = glm::dot(r.v,qvec) * inv_det;
	if (v < 0 || u + v > 1) return false;
	t = glm::dot(B,qvec) * inv_det;
	return (t > 0) ? true : false;
}

bool mesh::intersect(const ray& r, float& tNear, int& idx, float& u, float& v) const {
	bool intersection = false;
	auto start = std::chrono::high_resolution_clock::now();
	int j = 0;
	
	for (int i = 0; i < faces.size(); ++i) {
		float t = k_infinity;
		float uu = 0.0f;
		float vv = 0.0f;
		if (ray_triangle_intersect(r, vertices[faces[i].pts[0]], vertices[faces[i].pts[1]], vertices[faces[i].pts[2]], t, uu, vv) && t < tNear) {
			tNear = t;
			idx = i;
			u = uu;
			v = vv;
			intersection |= true;
		}
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<double, std::milli>(stop - start).count();
	if (MESH_DEBUG) std::cout << "Checked all triangles in object for intersections in " << duration/1000 << " seconds" << std::endl;

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

void mesh::get_shading_properties(glm::vec3& phit, glm::vec3& normal, const float& t_near,
								  const float& u, const float& v, const int& idx, const ray& r) const {
	phit = r.evaluate(t_near);
	bool smooth = true;
	if (!smooth) {
		const glm::vec3 v0 = vertices[faces[idx].pts[0]];
		const glm::vec3 v1 = vertices[faces[idx].pts[1]];
		const glm::vec3 v2 = vertices[faces[idx].pts[2]];
		normal = normalize(glm::cross((v1 - v0), (v2 - v0)));
	}
	else {
		const glm::vec3 n0 = normals[faces[idx].pts[0]];
		const glm::vec3 n1 = normals[faces[idx].pts[1]];
		const glm::vec3 n2 = normals[faces[idx].pts[2]];
		normal = normalize((1 - u - v) * n0 + u * n1 + v * n2);
	}
}

