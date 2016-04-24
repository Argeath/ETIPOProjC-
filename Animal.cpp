#include "main.h"

using namespace Game;
using namespace Utils;

void Animal::action()
{
	if (isDieing) return;

	Direction dir = getRandomDirection();
	if (dir == Direction::NONE) return;

	try
	{
		Organism* collider = world->getOrganismOnPos(position + dir);
		if (collider != nullptr)
			collision(collider, true);

		world->moveOrganism(this, dir);
	}
	catch (const Engine::InterruptActionException& e)
	{
	}
}

void Animal::collision(Organism* target, bool isAttacker /* = false */)
{
	if (((Animal*)target) != nullptr && timeSinceLastBreed > 10 && ((Animal*)target)->timeSinceLastBreed > 10 && alreadyBornChilds < ANIMAL_MAX_CHILD
		&& ((Animal*)target)->alreadyBornChilds < ANIMAL_MAX_CHILD && getType() != HUMAN && target->getType() == getType())
	{
		alreadyBornChilds++;
		((Animal*)target)->alreadyBornChilds++;
		breed(target);
		throw Engine::InterruptActionException();
	}

	if (target->getType() == getType()) return; // Bez kanibalizu

	if (isAttacker)
		target->collision(this);

	if (strength > target->strength || isAttacker && strength >= target->strength)
	{
		target->isDieing = true;
		target->onDie();

		if (isAttacker)
			world->window->logs->addLog(T("[") + T(world->round) + T("] ") + T(Organism::getOrganismNameByType(getType())) + T(" killed ") + T(Organism::getOrganismNameByType(target->getType())) + T("."));
	}
	else if (strength < target->strength && isAttacker)
	{
		isDieing = true;
		onDie();
		world->window->logs->addLog(T("[") + T(world->round) + T("] ") + T(Organism::getOrganismNameByType(getType())) + T(" attacked ") + T(Organism::getOrganismNameByType(target->getType())) + T(" and died."));
		throw Engine::InterruptActionException();
	}
}

