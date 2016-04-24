#include "main.h"

using namespace Engine;

int main(int argc, char *argv[]) {

	if(MAP_HEIGHT < 20 || MAP_WIDTH < 20)
	{
		printf("Map too small...");
		return 0;
	}

	srand(time(nullptr));

	Window* window = new Window();
	window->setActive();

	if (window->init() == 1)
		return 1;

	window->loop();
	window->quitWindow();

	delete window;
	return 0;
};
