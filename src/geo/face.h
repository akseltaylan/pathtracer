#ifndef FACE_H
#define FACE_H

#include <vector>
#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class face {
	public:
		// hold indices to pts, normals, and uvs within the corresponding obj_mesh
		std::vector<int> pts;
		std::vector<int> normals;
		std::vector<int> uvs;
		glm::vec3 v0;
		glm::vec3 v1;
		glm::vec3 v2;
		glm::vec3 A;
		glm::vec3 B;
		glm::vec3 normal;

		face(std::vector<int>, std::vector<int>, std::vector<int>);

		void set_normal(std::vector<glm::vec3>, bool);
		glm::vec3 get_normal(std::vector<glm::vec3>, bool);
		glm::vec3 get_normal();

	private:
		bool isQuad;

};

#endif