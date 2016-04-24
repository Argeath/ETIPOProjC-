#pragma once

namespace Game
{
	class Animal : public Organism
	{
		int alreadyBornChilds;
	public:
		int timeSinceLastBreed;

		Animal(World* w) : Organism(w), alreadyBornChilds(0), timeSinceLastBreed(0)
		{
		}

		void action() override;
		void collision(Organism* target, bool isAttacker = false) override;

		void onDie() override
		{
		}
	};
}

