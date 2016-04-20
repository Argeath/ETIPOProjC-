#include "main.h"

using namespace Game;
using namespace Utils;

void World::update()
{
	organisms.sort(compareOrganismsByInitiative);

	std::list<Organism*>::iterator it = organisms.begin();
	while(it != organisms.end())
	{
		if ((*it)->isDieing) {
			organismMap[(*it)->position.y][(*it)->position.x] = nullptr;
			delete *it;
			it = organisms.erase(it);
		}
		else {
			(*it)->age++;
			(*it)->action();
			++it;
		}
	}
	render();
}

void World::render()
{
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

		stopDraw = startDraw + windowGameSize + V2(2, 1);
	}

	for (int iy = startDraw.y, yy = 0; iy < stopDraw.y; iy++, yy++) {
		move(yy + window->mapStart.y, window->mapStart.x);
		for (int ix = startDraw.x, xx = 0; ix < stopDraw.x; ix++, xx+=2) {
			if(organismMap[iy][ix] != nullptr) {
				addch(organismMap[iy][ix]->appearance.sign | organismMap[iy][ix]->appearance.colors);
				addch(organismMap[iy][ix]->appearance.sign | organismMap[iy][ix]->appearance.colors);
			} else
			{
				addch(' ' | COLOR_PAIR(1));
				addch(' ' | COLOR_PAIR(1));
			}
		}
	}	
}

void World::createRandomOrganisms()
{
	for (int type = WOLF; type <= SOW_THISTLE; type++)
	{
		int amount = (rand() % 3) + 2;
		for (int i = 0; i < amount; i++)
			createOrganism((OrganismType)type);
	}
}

void World::createOrganism(OrganismType type)
{
	Organism* organism = Organism::getOrganismByType(type, this);

	if (organism == nullptr) return;

	int posX = rand() % MAP_WIDTH;
	int posY = rand() % MAP_HEIGHT;
	organism->position = V2(posX, posY);

	addOrganism(organism);
}



void World::addOrganism(Organism* organism)
{
	if (getOrganismOnPos(organism->position) == nullptr) {
		organisms.push_back(organism);
		organismMap[organism->position.y][organism->position.x] = organism;
	}
}

Organism* World::getOrganismOnPos(Utils::Vector2<int> pos)
{
	return organismMap[pos.y][pos.x];
	/*for (std::list<Organism*>::iterator it = organisms.begin(); it != organisms.end(); ++it)
		if ((*it)->position == pos)
			return *it;
	return nullptr;*/
}

void World::moveOrganism(Organism* organism, Utils::Direction dir)
{
	organismMap[organism->position.y][organism->position.x] = nullptr;

	organism->position += dir;
	organismMap[organism->position.y][organism->position.x] = organism;
}

bool World::compareOrganismsByInitiative(const Organism* a, const Organism* b)
{
	if (a->initiative == b->initiative) return (a->age > b->age);
	return (a->initiative > b->initiative);
}



