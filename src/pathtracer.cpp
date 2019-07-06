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
	accel_struct = new bvh(_s);
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
		glm::vec3 phit, hit_normal;
		//obj->get_shading_properties(phit, hit_normal, t_near, u, v, tri_idx, r);
		// shading will happen here
		hit_color.y = 1.0f;
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

			if (DEBUG) {
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