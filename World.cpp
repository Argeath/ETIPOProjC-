#include "main.h"

using namespace Game;

void World::update()
{
	
}

void World::render()
{
	for (std::list<Organism*>::iterator it = organisms.begin(); it != organisms.end(); ++it)
		(*it)->draw();
}

