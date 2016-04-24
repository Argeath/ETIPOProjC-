#include "main.h"

using namespace std;
using namespace Game;
using namespace Utils;

void World::update(int input)
{
	round++;
	sort(organisms.begin(), organisms.end(), compareOrganismsByInitiative);

	for (vector<Organism*>::const_iterator it = organisms.begin(); it != organisms.end(); ++it)
	{
		if (! (*it)->isDieing)
		{
			(*it)->age++;
			if (((Animal*)*it) != nullptr)
				((Animal*)*it)->timeSinceLastBreed++;
			(*it)->action();
			if ((*it)->getType() == HUMAN)
				((Player*)(*it))->handleInput(input);
		}
	}

	for (vector<Organism*>::const_iterator it = organisms.begin(); it != organisms.end();)
	{
		if ((*it)->isDieing)
		{
			if (organismMap[(*it)->position.y][(*it)->position.x] == *it)
				organismMap[(*it)->position.y][(*it)->position.x] = nullptr;
			delete *it;
			it = organisms.erase(it);
		}
		else ++it;
	}

	for (vector<Organism*>::const_iterator it = toBorn.begin(); it != toBorn.end(); ++it)
	{
		organisms.push_back(*it);
	}
	toBorn.clear();

	render();
}

void World::render()
{
	Vector2<int> windowSize = window->mapEnd - window->mapStart;
	Vector2<int> windowGameSize = V2(windowSize.x / 2, windowSize.y);
	Vector2<int> mapSize = V2(MAP_WIDTH, MAP_HEIGHT);

	Vector2<int> startDraw = V2(0, 0);
	Vector2<int> stopDraw = mapSize;

	if (windowGameSize < mapSize)
	{
		Vector2<int> half = windowGameSize / 2;
		startDraw = window->centerPosition - half;
		if (startDraw.y < 0) startDraw.y = 0;
		if (startDraw.x < 0) startDraw.x = 0;
		if (startDraw.y > mapSize.y - windowGameSize.y)
			startDraw.y = mapSize.y - windowGameSize.y;
		if (startDraw.x > mapSize.x - windowGameSize.x)
			startDraw.x = mapSize.x - windowGameSize.x;

		stopDraw = startDraw + windowGameSize;
	}

	for (int iy = startDraw.y, yy = 0; iy < stopDraw.y; iy++ , yy++)
	{
		move(yy + window->mapStart.y, window->mapStart.x);
		for (int ix = startDraw.x, xx = 0; ix < stopDraw.x; ix++ , xx += 2)
		{
			if (organismMap[iy][ix] != nullptr)
			{
				addch(organismMap[iy][ix]->appearance.sign | organismMap[iy][ix]->appearance.colors);
				addch(organismMap[iy][ix]->appearance.sign | organismMap[iy][ix]->appearance.colors);
			}
			else
			{
				addch(' ' | COLOR_PAIR(1));
				addch(' ' | COLOR_PAIR(1));
			}
		}
	}
}

void World::createRandomOrganisms()
{
	int rozmiar = sqrt(MAP_HEIGHT * MAP_WIDTH) / 5;
	for (int type = WOLF; type <= SOW_THISTLE; type++)
	{
		int amount = (rand() % rozmiar) + rozmiar / 2;
		for (int i = 0; i < amount; i++)
			createOrganism((OrganismType)type);
	}
}

Organism* World::createOrganism(OrganismType type)
{
	Organism* organism = Organism::getOrganismByType(type, this);

	if (organism == nullptr) return nullptr;

	int posX = rand() % MAP_WIDTH;
	int posY = rand() % MAP_HEIGHT;
	organism->position = V2(posX, posY);

	addOrganism(organism);
	return organism;
}


void World::createPlayer()
{
	Player* p = (Player*)createOrganism(HUMAN);
	if (p == nullptr) return; // TODO: Throw exception

	player = p;
	window->centerPosition = player->position;
}

void World::addOrganism(Organism* organism)
{
	if (getOrganismOnPos(organism->position) == nullptr)
	{
		toBorn.push_back(organism);
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

