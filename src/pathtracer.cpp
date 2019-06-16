#include "pathtracer.h"

pathtracer::pathtracer() {
	image * im;
	img = im;
	eyept = glm::vec3(0.0f, 0.0f, 1000.0f);
}

pathtracer::pathtracer(image * m_img) {
	img = m_img;
	eyept = glm::vec3(0.0f, 0.0f, 20.0f);
}

void pathtracer::set_scene(scene * _s) {
	s = _s;
}

object *  pathtracer::trace(const std::vector<object*>& objs, const ray & r, float & tNear) {
	int closest = -1;
	object * hit_obj = nullptr;
	float max = std::numeric_limits<float>::infinity();
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < objs.size(); ++i) {
		float tNearTri = max;
		if (objs[i]->obj_mesh.intersect(r, tNearTri) && tNearTri < tNear) {
			hit_obj = objs[i];
			tNear = tNearTri;
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = stop - start;
	if (DEBUG) std::cout << "Checked all objects in scene for intersections in " << duration.count() << " seconds" << std::endl;
	return hit_obj;
}

glm::vec3 pathtracer::cast(const std::vector<object*>& objs, const ray & r) {
	++num_rays;
	glm::vec3 hit_color = glm::vec3(0.0f, 0.0f, 0.0f);
	float tNear = std::numeric_limits<float>::infinity();
	if (trace(objs, r, tNear) != nullptr) {
		//glm::vec3 hit_pt = r.evaluate(tNear);
		hit_color.y = 1.0f;
	}
	return hit_color;
}

void pathtracer::render() {

	glClear(GL_COLOR_BUFFER_BIT);

	// TODO: set up scene / get scene data

	implane ip(img->width, img->height);
	int pixel_ct = 1;
	std::vector<object*> objs = s->get_objs();
	// TODO: build upon this basic render loop
	for (int i = 0; i < img->height; ++i) {
		for (int j = 0; j < img->width; ++j) {
			if (pixel_ct % 1000 == 0) {
				std::cout << pixel_ct << std::endl;
			}
			auto start = std::chrono::high_resolution_clock::now();
			glm::vec3 pixel_color(0.0f, 0.0f, 0.0f);
			glm::vec3 cur_pixel = ip.nextpixel();
			//TODO: implement BVH
			ray primary_ray(eyept, cur_pixel - eyept);
			pixel_color = cast(objs,primary_ray);
			img->set_pixel(j, i, pixel_color);
			++pixel_ct;
			if (DEBUG) {
				auto stop = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> duration = stop - start;
				std::cout << "Computed pixel in " << duration.count() << " seconds" << std::endl;
			}
		}
	}

	img->create_image();
}