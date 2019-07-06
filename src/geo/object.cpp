#include "object.h"

object::object() {

}

object::~object() {

}

glm::vec3 object::get_albedo() const {
	return albedo;
}

material * object::get_material() const {
	return mat;
}

void object::set_albedo(glm::vec3 _albedo) {
	albedo = _albedo;
}

void object::set_material(material * _mat) {
	mat = _mat;
}
 
