#include "main.h"

using namespace Game;
using namespace Utils;

void Animal::action()
{
	if (isDieing) return;

	Direction dir = getRandomDirection();
	if (dir == Direction::NONE) return;

	try {
		Organism* collider = world->getOrganismOnPos(position + dir);
		if (collider != nullptr)
			collision(collider, true);

		world->moveOrganism(this, dir);
	} catch(const Engine::InterruptActionException& e) {}
}

void Animal::collision(Organism* target, bool isAttacker /* = false */)
{
	if (timeSinceLastBreed > 10 && target->timeSinceLastBreed > 10 && getType() != HUMAN && target->getType() == getType())
	{
		breed(target);
		throw Engine::InterruptActionException();
	}

	if (target->getType() == getType()) return; // Bez kanibalizu

	if(isAttacker)
		target->collision(this);

	if (strength > target->strength || isAttacker && strength >= target->strength)
		target->isDieing = true;
	else if (strength < target->strength && isAttacker) {
		isDieing = true;
		throw Engine::InterruptActionException();
	}
}