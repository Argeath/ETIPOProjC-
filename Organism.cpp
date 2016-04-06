#include "main.h"

using namespace Game;

void Organism::draw()
{
	world->buffer[position.y][position.x] = sign;
}

