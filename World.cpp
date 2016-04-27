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
		if (! (*it)->getIsDieing())
		{
			(*it)->increaseAge();
			if (((Animal*)*it) != nullptr)
				((Animal*)*it)->increaseTimeSinceLastBreed();
			(*it)->action();
			if ((*it)->getType() == HUMAN)
				((Player*)(*it))->handleInput(input);
		}
	}

	for (vector<Organism*>::const_iterator it = organisms.begin(); it != organisms.end();)
	{
		if ((*it)->getIsDieing())
		{
			if (organismMap[(*it)->getPos().y][(*it)->getPos().x] == *it)
				organismMap[(*it)->getPos().y][(*it)->getPos().x] = nullptr;
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
	Vector2<int> windowSize = window->getMapEnd() - window->getMapStart();
	Vector2<int> windowGameSize = V2(windowSize.x / 2, windowSize.y);

	Vector2<int> startDraw = V2(0, 0);
	Vector2<int> stopDraw = size;

	if (windowGameSize < size)
	{
		Vector2<int> half = windowGameSize / 2;
		startDraw = window->getCenterPos() - half;
		if (startDraw.y < 0) startDraw.y = 0;
		if (startDraw.x < 0) startDraw.x = 0;
		if (startDraw.y > size.y - windowGameSize.y)
			startDraw.y = size.y - windowGameSize.y;
		if (startDraw.x > size.x - windowGameSize.x)
			startDraw.x = size.x - windowGameSize.x;

		stopDraw = startDraw + windowGameSize;
	}

	for (int iy = startDraw.y, yy = 0; iy < stopDraw.y; iy++ , yy++)
	{
		move(yy + window->getMapStart().y, window->getMapStart().x);
		for (int ix = startDraw.x, xx = 0; ix < stopDraw.x; ix++ , xx += 2)
		{
			if (organismMap[iy][ix] != nullptr)
			{
				addch(organismMap[iy][ix]->getAppearance().sign | organismMap[iy][ix]->getAppearance().colors);
				addch(organismMap[iy][ix]->getAppearance().sign | organismMap[iy][ix]->getAppearance().colors);
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
	int rozmiar = sqrt(size.y * size.x) / 5;
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

	int posX = rand() % size.x;
	int posY = rand() % size.y;
	organism->setPosition(V2(posX, posY));

	addOrganism(organism);
	return organism;
}


void World::init()
{
	createPlayer();
	createRandomOrganisms();
}

void World::createPlayer()
{
	Player* p = (Player*)createOrganism(HUMAN);
	if (p == nullptr) return; // TODO: Throw exception

	player = p;
	window->setCenterPos(player->getPos());
}

void World::addOrganism(Organism* organism)
{
	if (getOrganismOnPos(organism->getPos()) == nullptr)
	{
		toBorn.push_back(organism);
		organismMap[organism->getPos().y][organism->getPos().x] = organism;
	}
}

Organism* World::getOrganismOnPos(Utils::Vector2<int> pos) const
{
	return organismMap[pos.y][pos.x];
	/*for (std::list<Organism*>::iterator it = organisms.begin(); it != organisms.end(); ++it)
		if ((*it)->position == pos)
			return *it;
	return nullptr;*/
}

void World::moveOrganism(Organism* organism, Utils::Direction dir) const
{
	organismMap[organism->getPos().y][organism->getPos().x] = nullptr;

	organism->setPosition(organism->getPos() + dir);
	organismMap[organism->getPos().y][organism->getPos().x] = organism;
}

void World::save(std::ofstream& _out)
{
	//_out << MAP_WIDTH << MAP_HEIGHT << round << isPlayerMove;
	io::write(_out, size.x);
	io::write(_out, size.y);
	io::write(_out, round);
	io::write(_out, isPlayerMove);
	io::write(_out, player->getToNextSpell());

	//window->logs->save(_out);

	//_out << organisms.size();
	io::write(_out, organisms.size());
	for (vector<Organism*>::const_iterator it = organisms.begin(); it != organisms.end(); ++it)
		(*it)->save(_out);
}

World* World::load(std::ifstream& _in, Engine::Window* window)
{
	int round;
	Vector2<int> size;
	bool isPlayerMove;
	int toNextSpell;
	//_in >> width >> height >> round >> isPlayerMove;
	io::read(_in, size.x);
	io::read(_in, size.y);
	io::read(_in, round);
	io::read(_in, isPlayerMove);
	io::read(_in, toNextSpell);

	World* world = new World(window, size);

	window->resize(size);

	if (size < V2(15, 15) || size > V2(60, 60))
		throw new Engine::LoadingMapException("Wrong map size.");

	if (round < 0)
		throw new Engine::LoadingMapException("Invalid round.");

	//window->logs->load(_in);
	//window->printLogs();

	int organismAmount = 0;
	io::read(_in, organismAmount);
	//_in >> organismAmount;
	for (int i = 0; i < organismAmount; i++)
	{
		Organism* organism = Organism::load(_in, world);
		if (organism == nullptr)
			throw new Engine::LoadingMapException("Error while loading organism");

		world->addOrganism(organism);

		if (organism->getType() == HUMAN)
		{
			world->player = (Player*)organism;
			world->player->setToNextSpell(toNextSpell);
		}
	}

	window->setCenterPos(world->player->getPos());
	return world;
}

bool World::compareOrganismsByInitiative(const Organism* a, const Organism* b)
{
	if (a->getInitative() == b->getInitative()) return (a->getAge() > b->getAge());
	return (a->getInitative() > b->getInitative());
}

