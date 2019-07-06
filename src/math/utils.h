#define GLEW_STATIC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

glm::vec3 normalize(const glm::vec3&);
glm::vec3 reflected(const glm::vec3&, const glm::vec3&);
bool quadratic_formula(const float &, const float &, const float &, float &, float &);
void debug_vec3(const glm::vec3&, const std::string&);
