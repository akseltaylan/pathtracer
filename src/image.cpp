#include "image.h"

image::image() : width(500), height(500) {
	pixels = new float[3 * width * height];

	glfwInit();
	glfwSetTime(0.0);

	pWindow = glfwCreateWindow(width, height, "pathtracer", NULL, NULL);

	glfwMakeContextCurrent(pWindow);
	//glfwSetKeyCallback(pWindow, KeyCallbackFunc);
	glewExperimental = true;
	glewInit();
	glViewport(0, 0, width, height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	clear_image();
}

image::image(int w, int h) : width(w), height(h) {
	pixels = new float[3 * width * height];

	glfwInit();
	glfwSetTime(0.0);

	pWindow = glfwCreateWindow(width, height, "pathtracer", NULL, NULL);

	glfwMakeContextCurrent(pWindow);
	//glfwSetKeyCallback(pWindow, KeyCallbackFunc);
	glewExperimental = true;
	glewInit();
	glViewport(0, 0, width, height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	clear_image();
}

// Draws the scene
void image::draw(void)
{
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
}

// Clears framebuffer to black
void image::clear_image()
{
	memset(pixels, 0, width * height * sizeof(float));
}

// Origin is lower left corner, x positive is right side, y positive is upwards.
void image::set_pixel(int x, int y, float R, float G, float B)
{
	pixels[(y * width + x) * 3] = R;
	pixels[(y * width + x) * 3 + 1] = G;
	pixels[(y * width + x) * 3 + 2] = B;
}

void image::set_pixel(int x, int y, vec4 color)
{
	pixels[(y * width + x) * 3] = color.x;	   // R	
	pixels[(y * width + x) * 3 + 1] = color.y; // G
	pixels[(y * width + x) * 3 + 2] = color.z; // B
}

void image::create_image()
{
	while (!glfwWindowShouldClose(pWindow)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw();
		glFlush();
		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}
	delete[] pixels;
}