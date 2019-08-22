#ifndef MATERIAL_H
#define MATERIAL_H

#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "texture.h"



class material {
	private:
		glm::vec3 albedo;
		texture * tex;
	public:
		enum mat_type {
			diffuse, specular, glass
		};
		float ka;
		float kd;
		float ks;
		float alpha;
		glm::vec3 emissive;
		mat_type mtype;
		material();
		material(const float&, const float&, const float&, const float&, const glm::vec3&);
		material(const float&, const float&, const float&, const float&, const glm::vec3&, const glm::vec3&, mat_type);
		void set_texture(texture *);
		glm::vec3 get_albedo(glm::vec2);
		void set_albedo(glm::vec3);
};

#endif
