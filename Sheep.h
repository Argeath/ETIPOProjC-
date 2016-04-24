#pragma once

namespace Game
{
	class Sheep : public Animal
	{
	public:

		Sheep(World* w) : Animal(w)
		{
			appearance.sign = 'S';
			appearance.colors = COLOR_PAIR(8) | A_BOLD;
			strength = 9;
			initiative = 5;
		}

		OrganismType getType() override
		{
			return SHEEP;
		}
	};
}

