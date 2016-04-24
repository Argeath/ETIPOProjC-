#include "main.h"

using namespace Game;
using namespace Utils;

void Player::action() {}

void Player::handleInput(int input)
{
	switch(input) {
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
	world->window->showWindow(Engine::FinishGame);
}

bool Player::move(Utils::Direction dir)
{
	if(position + dir < V2(0, 0) || position + dir >= MAP_SIZE) {
		return false;
	}
	try {
		Organism* collider = world->getOrganismOnPos(position + dir);
		if (collider != nullptr)
			collision(collider, true);

		world->moveOrganism(this, dir);
		world->window->centerPosition = position;
	} catch(Engine::InterruptActionException e) {}
	return true;
}

