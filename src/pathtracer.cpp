#include "pathtracer.h"

pathtracer::pathtracer() {
	image * im;
	img = im;
	eyept = vec4(0.0f, 0.0f, 1000.0f);
}

pathtracer::pathtracer(image * m_img) {
	img = m_img;
	eyept = vec4(0.0f, 0.0f, 250.0f);
}

void pathtracer::set_scene(scene * _s) {
	s = _s;
}

Sphere *  pathtracer::trace(ray & r, float & tNear) {
	int closest = -1;
	Sphere * hit_obj = nullptr;
	float max = std::numeric_limits<float>::infinity();
	for (int i = 0; i < s->get_objs().size(); ++i) {
		//std::cout << "check obj " << i << std::endl;
		float tNearTri = max;
		//if (s->get_objs()[i]->obj_mesh.intersect(r, tNearTri)) {
		if (s->get_objs()[i]->intersect(r, tNearTri)) {
			//std::cout << "hit something!" << std::endl;
			hit_obj = s->get_objs()[i];
			tNear = tNearTri;
		}
	}
	return hit_obj;
}

vec4 pathtracer::cast(ray & r) {
	vec4 hit_color = vec4(0.0f, 0.0f, 0.0f);
	float tNear = std::numeric_limits<float>::infinity();
	if (trace(r, tNear) != nullptr) {
		//std::cout << "do i ever get here?" << std::endl;
		vec4 hit_pt = r.evaluate(tNear);
		hit_color.y = 1.0f;
	}
	return hit_color;
}

void pathtracer::render() {

	glClear(GL_COLOR_BUFFER_BIT);

	// TODO: set up scene / get scene data

	implane ip(img->width, img->height);

	// TODO: build upon this basic render loop
	for (int i = 0; i < img->height; ++i) {
		for (int j = 0; j < img->width; ++j) {

			vec4 pixel_color(0.0f, 0.0f, 0.0f);
			vec4 cur_pixel = ip.nextpixel();
			//TODO: figure out what's going on with cur_pixel / ip
			ray primary_ray(eyept, cur_pixel - eyept);
			//std::cout << primary_ray.v.x << " " << primary_ray.v.y << " " << primary_ray.v.z << std::endl;
			//TODO: add color from ray cast here
			pixel_color = cast(primary_ray);
			img->set_pixel(j, i, pixel_color);
		}
	}

	img->create_image();
}