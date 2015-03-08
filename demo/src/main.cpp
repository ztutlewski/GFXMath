#include "glapplication.h"

using namespace gofxengine;


size_t width = 640;
size_t height = 480;

int main()
{
	GLApplication application;

	if (!application.InitGLFW())
		return -1;

	application.InitWindowed(3, 2, width, height, "GFX Engine");


	return application.StartGameLoop();
}