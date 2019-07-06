#ifndef LIGHT_H
#define LIGHT_H

#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class light {
	protected:
		glm::vec3 position;
		glm::vec3 ia;
		glm::vec3 id;
		glm::vec3 is;
	public:
		light();
		light(const glm::vec3&);
		virtual glm::vec3 get_pos() = 0;
		glm::vec3 get_intensity(const char&);
		void set_intensity(const glm::vec3&, const glm::vec3&, const glm::vec3&);
};

#endif
