#include "main.h"

using namespace Game;
using namespace Utils;

void World::update()
{
	
}

void World::render()
{
	for (int iy = 0; iy < MAP_HEIGHT; iy++)
		for (int ix = 0; ix < MAP_WIDTH; ix++)
			buffer[iy][ix] = ' ';

	for (std::list<Organism*>::iterator it = organisms.begin(); it != organisms.end(); ++it)
		(*it)->draw();

	Vector2<int> windowSize = window->mapEnd - window->mapStart;
	Vector2<int> windowGameSize = V2(windowSize.x / 2, windowSize.y);
	Vector2<int> mapSize = V2(MAP_WIDTH, MAP_HEIGHT);

	Vector2<int> startDraw = V2(0, 0);
	Vector2<int> stopDraw = mapSize;

	if(windowGameSize < mapSize)
	{
		startDraw = window->centerPosition - windowGameSize / 2;
		if (startDraw < V2(0, 0))
			startDraw = V2(0, 0);
		else if (startDraw > mapSize - windowGameSize)
			startDraw = mapSize - windowGameSize;

		stopDraw = startDraw + windowGameSize;
	}
	for (int iy = startDraw.y, yy = 0; iy < stopDraw.y; iy++, yy++) {
		move(yy + window->mapStart.y, window->mapStart.x);
		for (int ix = startDraw.x; ix < stopDraw.x; ix++) {
			addch(buffer[iy][ix]);
			addch(buffer[iy][ix]);
		}
	}

		
}

