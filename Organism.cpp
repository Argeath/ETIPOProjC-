#include "main.h"

using namespace Game;
using namespace Utils;

Direction Organism::getRandomDirection(bool mustBeEmpty) const
{
	Direction possible_directions[4];
	int n = 0;

	if ((position.x > 0 && !mustBeEmpty) || (position.x > 0 && world->getOrganismOnPos(position + WEST) == nullptr))
		possible_directions[n++] = WEST;
	if ((position.y > 0 && !mustBeEmpty) || (position.y > 0 && world->getOrganismOnPos(position + NORTH) == nullptr))
		possible_directions[n++] = NORTH;
	if ((position.x + 1 < world->getSize().x && !mustBeEmpty) || (position.x + 1 < world->getSize().x && world->getOrganismOnPos(position + EAST) == nullptr))
		possible_directions[n++] = EAST;
	if ((position.y + 1 < world->getSize().y && !mustBeEmpty) || (position.y + 1 < world->getSize().y && world->getOrganismOnPos(position + EAST) == nullptr))
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
	if (thisAnimal != nullptr)
		thisAnimal->setTimeSinceLastBreed(0);
	if (otherParent != nullptr)
	{
		Animal* otherAnimal = (Animal*)otherParent;
		otherAnimal->setTimeSinceLastBreed(0);
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

Text Organism::getOrganismNameByType(OrganismType type)
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

void Organism::save(std::ofstream& _out)
{
	//_out << (int)getType();
	io::write(_out, (int)getType());
	//_out << age << strength << initiative << position.x << position.y;
	io::write(_out, age);
	io::write(_out, strength);
	io::write(_out, initiative);
	io::write(_out, position.x);
	io::write(_out, position.y);
	io::write(_out, appearance.sign);
	io::write(_out, appearance.colors);
	//_out << appearance.sign << appearance.colors;
}

Organism* Organism::load(std::ifstream& _in, World* world)
{
	int type;
	io::read(_in, type);
	Organism* organism = getOrganismByType((OrganismType)type, world);
	if (organism == nullptr) return nullptr;

	//_in >> organism->age >> organism->strength >> organism->initiative >> organism->position.x >> organism->position.y;
	//_in >> organism->appearance.sign >> organism->appearance.colors;

	io::read(_in, organism->age);
	io::read(_in, organism->strength);
	io::read(_in, organism->initiative);
	io::read(_in, organism->position.x);
	io::read(_in, organism->position.y);
	io::read(_in, organism->appearance.sign);
	io::read(_in, organism->appearance.colors);

	return organism;
}

