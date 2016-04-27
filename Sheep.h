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
			strength = 4;
			initiative = 4;
		}

		OrganismType getType() override
		{
			return SHEEP;
		}
	};
}

