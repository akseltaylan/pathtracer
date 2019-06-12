#include "pathtracer.h"

pathtracer::pathtracer() {
	image * im;
	img = im;
	eyept = vec4(0.0f, 0.0f, 1000.0f);
}

pathtracer::pathtracer(image * m_img) {
	img = m_img;
	eyept = vec4(0.0f, 0.0f, 1000.0f);
}

void pathtracer::render() {

	glClear(GL_COLOR_BUFFER_BIT);

	// TODO: set up scene / get scene data

	// TODO: create image plane
	implane ip(img->width, img->height);

	// TODO: build upon this basic render loop
	for (int i = 0; i < img->height; ++i) {
		for (int j = 0; j < img->width; ++j) {

			vec4 pixel_color(0.0, 0.0, 0.0);
			vec4 cur_pixel = ip.nextpixel();
			ray primary_ray(eyept, cur_pixel - eyept);
			//TODO: add color from ray cast here
			img->set_pixel(j, i, pixel_color);
		}
	}

	img->create_image();
}