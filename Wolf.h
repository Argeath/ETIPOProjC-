#pragma once

namespace Game
{
	class Wolf : public Animal
	{
	public:

		Wolf(World* w) : Animal(w)
		{
			appearance.sign = 'W';
			appearance.colors = COLOR_PAIR(8) | A_BOLD;
			strength = 9;
			initiative = 5;
		}

		OrganismType getType() override
		{
			return WOLF;
		}
	};
}

