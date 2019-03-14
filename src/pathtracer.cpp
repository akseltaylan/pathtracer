#include "pathtracer.h"

pathtracer::pathtracer() {
	image * im;
	img = im;
}

pathtracer::pathtracer(image * m_img) {
	img = m_img;
}

void pathtracer::render() {

	glClear(GL_COLOR_BUFFER_BIT);

	// TODO: set up scene / get scene data

	// TODO: create image plane

	// TODO: build upon this basic render loop
	for (int i = 0; i < img->height; ++i) {
		for (int j = 0; j < img->width; ++j) {

			vec4 pixel_color(0.0, 0.0, 0.0);

			img->set_pixel(j, i, pixel_color);
		}
	}

	img->create_image();
}