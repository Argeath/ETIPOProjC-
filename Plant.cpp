#include "main.h"

using namespace Game;
using namespace Utils;

void Plant::action()
{
	if (rand() % 1000 > PLANT_CHANCE) return;

	breed();
}

