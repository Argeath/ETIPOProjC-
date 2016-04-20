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
	} catch(Engine::InterruptActionException* e) {}
}

void Animal::collision(Organism* target, bool isAttacker /* = false */)
{
	if (target->getType() == getType() && getType() != HUMAN && age > 10 && target->age > 10)
	{
		breed();
		throw new Engine::InterruptActionException();
	}

	if (target->getType() == getType()) return; // Bez kanibalizu

	if(isAttacker)
		target->collision(this);

	if (strength > target->strength)
		target->isDieing = true;
	else if (strength < target->strength && isAttacker) {
		isDieing = true;
		throw new Engine::InterruptActionException();
	}
}