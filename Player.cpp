#include "main.h"

using namespace Game;
using namespace Utils;

void Player::action()
{
}

void Player::handleInput(int input)
{
	switch (input)
	{
	case KEY_UP:
		move(NORTH);
		break;
	case KEY_DOWN:
		move(SOUTH);
		break;
	case KEY_LEFT:
		move(WEST);
		break;
	case KEY_RIGHT:
		move(EAST);
		break;
	}
}

void Player::onDie()
{
	world->getWindow()->showWindow(Engine::FinishGame);
}

bool Player::move(Utils::Direction dir)
{
	if (position + dir < V2(0, 0) || position + dir >= world->getSize())
	{
		return false;
	}

	try
	{
		Organism* collider = world->getOrganismOnPos(position + dir);
		if (collider != nullptr)
			collision(collider, true);

		world->moveOrganism(this, dir);
		world->getWindow()->setCenterPos(position);

		if (toNextSpell > 5)
		{
			for (int iy = -1; iy <= 1; iy++)
				for (int ix = -1; ix <= 1; ix++)
				{
					if (iy == 0 && ix == 0) continue;
					Organism* organism = world->getOrganismOnPos(V2(position.x + ix, position.y + iy));
					if (organism != nullptr)
					{
						organism->setIsDieing();
						world->getWindow()->getLogs()->addLog(T("Player burned ") + T(getOrganismNameByType(organism->getType())));
					}
				}
		}

		if (toNextSpell > 0)
			toNextSpell--;
	}
	catch (Engine::InterruptActionException e)
	{
	}
	return true;
}

void Player::castSpell()
{
	if (toNextSpell > 0)
	{
		world->getWindow()->getLogs()->addLog(T("Do nastepnej aktywacji czaru: ") + T(toNextSpell));
		return;
	}
	toNextSpell = 10;
}

