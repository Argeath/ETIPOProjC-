#pragma once

namespace Game
{
	class Player : public Animal
	{
	public:
		Player(World* w) : Animal(w)
		{
			appearance.sign = 'P';
			appearance.colors = COLOR_PAIR(10) | A_BOLD;
			strength = 5;
			initiative = 4;
		}


		void action() override;
		bool move(Utils::Direction dir);
		void handleInput(int input);
		void onDie() override;

		OrganismType getType() override { return HUMAN; }
	};
}