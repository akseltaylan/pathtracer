#include "pathtracer.h"

pathtracer::pathtracer() {
	image * im;
	img = im;
	eyept = glm::vec3(0.0f, 0.0f, 1000.0f);
}

pathtracer::pathtracer(image * m_img) {
	img = m_img;
	pixels = new float[3 * img->width * img->height];
	eyept = glm::vec3(0.0f, 0.0f, 1000.0f);
}

void pathtracer::set_scene(scene * _s) {
	eyept = _s->get_camera();
	accel_struct = new bvh(_s);
	s = _s;
}

bool pathtracer::in_shadow(const ray& r, const glm::vec3& normal) {
	const float bias = .001f;
		
	ray shadow_ray(r.p, normalize(r.v - r.p));
	shadow_ray.p = r.p + bias * normal;
	float t = std::numeric_limits<float>::infinity();
	float u = std::numeric_limits<float>::infinity();
	float v = std::numeric_limits<float>::infinity();
	int idx = -1;
	return trace(shadow_ray, t, idx, u, v) != nullptr;
}

glm::vec3 pathtracer::compute_direct_lighting(const object * obj, const glm::vec3& phit, const glm::vec3& hit_normal) {
	glm::vec3 dl_contrib(0.0f, 0.0f, 0.0f);
	glm::vec3 ambient(0.0f);
	glm::vec3 diffuse(0.0f);
	glm::vec3 specular(0.0f);

	// compute ambient contribution
	const std::vector<light *>& lights = accel_struct->s->get_lights();
	ambient = obj->get_material()->ka * lights[0]->get_intensity('a');

	// go through every light in scene	
	for (int i = 0; i < lights.size(); ++i) {

		if (!in_shadow(ray(phit, lights[i]->get_pos() ), hit_normal) ) {

			// compute diffuse contribution of light
			glm::vec3 l_m = normalize(lights[i]->get_pos() - phit);
			if (glm::dot(l_m, hit_normal) > 0) diffuse += obj->get_material()->kd * glm::dot(l_m, hit_normal) * lights[i]->get_intensity('d');

			// compute specular contribution of light
			glm::vec3 r_m = reflected(-1.f * l_m, hit_normal);
			glm::vec3 view = normalize(eyept - phit);
			if (glm::dot(r_m, view) > 0 && glm::dot(l_m, hit_normal) > 0) {
				specular += obj->get_material()->ks * lights[i]->get_intensity('s') * powf(glm::dot(r_m, view), obj->get_material()->alpha);
			}
		}
	}

	dl_contrib += ambient;
	dl_contrib += diffuse;
	dl_contrib += specular;

	return dl_contrib;
}

const object * pathtracer::trace(const ray & r, float & t_near, int& tri_idx, float& u, float& v) {
	int closest = -1;
	const object * hit_obj = nullptr;
	hit_obj = accel_struct->intersect(r, t_near, tri_idx, u, v);
	return hit_obj;
}

glm::vec3 pathtracer::cast(const ray & r) {
	++num_rays;
	glm::vec3 hit_color = glm::vec3(0.0f, 0.0f, 0.0f);
	float t_near = std::numeric_limits<float>::infinity();
	float u = std::numeric_limits<float>::infinity();
	float v = std::numeric_limits<float>::infinity();
	int tri_idx = -1;
	const object * obj = trace(r, t_near, tri_idx, u, v);
	if (obj != nullptr) {
		glm::vec3 phit = glm::vec3(0.0f);
		glm::vec3 hit_normal = glm::vec3(0.0f);
		obj->get_shading_properties(phit, hit_normal, t_near, u, v, tri_idx, r);
		glm::vec3 dl = compute_direct_lighting(obj, phit, hit_normal);
		glm::vec3 il = glm::vec3(0.0f); // TODO: indirect lighting
		hit_color = (dl + il) * obj->get_albedo();
	}
	else {
		hit_color = s->bg_color;
	}
	return hit_color;
}

void pathtracer::render() {

	glClear(GL_COLOR_BUFFER_BIT);

	// get scene data
	auto start = std::chrono::high_resolution_clock::now();

	implane * ip = new implane(img->width, img->height);
	std::vector<object*> objs = accel_struct->s->get_objs();
	
	for (int i = 0; i < img->height; ++i) {
		for (int j = 0; j < img->width; ++j) {

			auto start = std::chrono::high_resolution_clock::now();
			glm::vec3 pixel_color(0.0f, 0.0f, 0.0f);
			glm::vec3 cur_pixel = ip->nextpixel();
			ray primary_ray(eyept, cur_pixel - eyept);
			pixel_color = cast(primary_ray);
			img->set_pixel(j, i, pixel_color);

			if (PIXEL_DEBUG) {
				auto stop = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration<double, std::milli>(stop - start).count();
				std::cout << "Computed pixel in " << duration / 1000 << " seconds" << std::endl;
			}
		}
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<double, std::milli>(stop - start).count();
	std::cout << "Rendered image in " << duration / 1000 << " seconds" << std::endl;
	img->create_image();
}