#pragma once

namespace Game
{
	class Player : public Animal
	{
		int toNextSpell;
	public:
		Player(World* w) : Animal(w), toNextSpell(0)
		{
			appearance.sign = 'P';
			appearance.colors = COLOR_PAIR(10) | A_BOLD;
			strength = 5;
			initiative = 4;
		}

		int getToNextSpell() const
		{
			return toNextSpell;
		}

		void setToNextSpell(int value)
		{
			toNextSpell = value;
		}

		void action() override;
		bool move(Utils::Direction dir);
		void castSpell();
		void handleInput(int input);
		void onDie() override;

		OrganismType getType() override
		{
			return HUMAN;
		}
	};
}

