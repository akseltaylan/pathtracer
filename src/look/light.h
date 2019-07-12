#ifndef LIGHT_H
#define LIGHT_H

#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class light {
	protected:
		glm::vec3 position;
		float intensity;
		glm::vec3 color;
	public:
		light();
		float get_intensity() const;
		glm::vec3 get_color() const;
		void set_intensity(const float&);
		virtual glm::vec3 get_pos() const = 0;
};

#endif
