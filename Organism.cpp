#include "main.h"

using namespace Game;

void Organism::draw()
{
	DrawSurface(world->window->resourceManager->getResourceByName(spriteName)->source, position.x * 32 + 16, position.y * 32 + 16);
}

