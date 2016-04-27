#pragma once

namespace Game
{
	class Guarana : public Plant
	{
	public:
		Guarana(World* w) : Plant(w)
		{
			appearance.sign = 'G';
			appearance.colors = COLOR_PAIR(3) | A_BOLD;
		}

		void collision(Organism* target, bool isAttacker) override
		{
			target->setStrength(target->getStrength() + 3);
		}

		OrganismType getType() override
		{
			return GUARANA;
		}
	};
}

