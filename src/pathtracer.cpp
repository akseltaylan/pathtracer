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

bool  pathtracer::trace(const std::vector<object*>& objs, const ray & r, float & t_near) {
	int closest = -1;
	const object * hit_obj = nullptr;
	float max = std::numeric_limits<float>::infinity();
	
	hit_obj = accel_struct->intersect(r, t_near);
	float tn = max;
	if (hit_obj == nullptr) return false;
	else {
		if (hit_obj->intersect(r, tn) && tn < t_near) {
			t_near = tn;
			return true;
		}
		return false;
	}
}

glm::vec3 pathtracer::cast(const std::vector<object*>& objs, const ray & r) {
	++num_rays;
	glm::vec3 hit_color = glm::vec3(0.0f, 0.0f, 0.0f);
	float t_near = std::numeric_limits<float>::infinity();
	if (trace(objs, r, t_near)) {
		hit_color.y = 1.0f;
	}
	return hit_color;
}

void pathtracer::render() {

	glClear(GL_COLOR_BUFFER_BIT);

	// get scene data
	auto start = std::chrono::high_resolution_clock::now();

	implane * ip = new implane(img->width, img->height);
	std::size_t max = img->width * img->height;

	std::size_t cores = std::thread::hardware_concurrency();
	volatile std::atomic<std::size_t> count(0);
	std::vector<std::future<void>> future_vec;

	int pixel_ct = 1;
	std::vector<object*> objs = accel_struct->s->get_objs();
	
	for (int i = 0; i < img->height; ++i) {
		for (int j = 0; j < img->width; ++j) {

			auto start = std::chrono::high_resolution_clock::now();
			glm::vec3 pixel_color(0.0f, 0.0f, 0.0f);
			glm::vec3 cur_pixel = ip->nextpixel();

			ray primary_ray(eyept, cur_pixel - eyept);
			pixel_color = cast(objs, primary_ray);
			img->set_pixel(j, i, pixel_color);
			++pixel_ct;
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