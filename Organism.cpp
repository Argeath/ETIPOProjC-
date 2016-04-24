#include "main.h"

using namespace Game;
using namespace Utils;

Direction Organism::getRandomDirection(bool mustBeEmpty) const
{
	Direction possible_directions[4];
	int n = 0;
	
	if((position.x > 0 && !mustBeEmpty) || (position.x > 0 && world->getOrganismOnPos(position + WEST) == nullptr))
		possible_directions[n++] = WEST;
	if ((position.y > 0 && !mustBeEmpty) || (position.y > 0 && world->getOrganismOnPos(position + NORTH) == nullptr))
		possible_directions[n++] = NORTH;
	if ((position.x + 1 < MAP_WIDTH && !mustBeEmpty) || (position.x + 1 < MAP_WIDTH && world->getOrganismOnPos(position + EAST) == nullptr))
		possible_directions[n++] = EAST;
	if ((position.y + 1 < MAP_HEIGHT && !mustBeEmpty) || (position.y + 1 < MAP_HEIGHT && world->getOrganismOnPos(position + EAST) == nullptr))
		possible_directions[n++] = SOUTH;

	if (n == 0) return Direction::NONE;
	return possible_directions[rand() % n];
}

void Organism::breed(Organism* otherParent)
{
	Direction dir = getRandomDirection(true);
	if (dir == Direction::NONE) return;

	Organism* organism = getOrganismByType(getType(), world);
	if (organism == nullptr) return;

	organism->position = position + dir;
	world->addOrganism(organism);

	Animal* thisAnimal = (Animal*)this;
	if(thisAnimal != nullptr)
		thisAnimal->timeSinceLastBreed = 0;
	if (otherParent != nullptr) {
		Animal* otherAnimal = (Animal*)otherParent;
		otherAnimal->timeSinceLastBreed = 0;
	}
}

Organism* Organism::getOrganismByType(OrganismType type, World* world)
{
	Organism* organism = nullptr;
	switch (type)
	{
	case HUMAN:
		organism = new Player(world);
		break;
	case WOLF:
		organism = new Wolf(world);
		break;
	case SHEEP:
		organism = new Sheep(world);
		break;
	case TURTLE:
		organism = new Turtle(world);
		break;
	case ANTELOPE:
		organism = new Antelope(world);
		break;
	case FOX:
		organism = new Fox(world);
		break;
	case GRASS:
		organism = new Grass(world);
		break;
	case GUARANA:
		organism = new Guarana(world);
		break;
	case SOW_THISTLE:
		organism = new SowThistle(world);
		break;
	case WOLFBERRY:
		organism = new Wolfberry(world);
		break;
	case NONE:
	default: 
		break;
	}

	return organism;
}

Utils::Text Organism::getOrganismNameByType(OrganismType type)
{
	switch (type)
	{
	case HUMAN:
		return "Player";
	case WOLF:
		return "Wolf";
	case SHEEP:
		return "Sheep";
	case TURTLE:
		return "Turtle";
	case ANTELOPE:
		return "Antelope";
	case FOX:
		return "Fox";
	case GRASS:
		return "Grass";
	case GUARANA:
		return "Guarana";
	case SOW_THISTLE:
		return "Sow Thistle";
	case WOLFBERRY:
		return "Wolfberry";
	case NONE:
	default:
		return "Unknown";
	}
}
