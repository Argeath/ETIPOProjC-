#include "main.h"

using namespace Game;

void World::update(double deltaTime)
{
	
}

void World::render()
{
	for (list<Organism*>::iterator it = organisms.begin(); it != organisms.end(); ++it)
		(*it)->draw();
}

