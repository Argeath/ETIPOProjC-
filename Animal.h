#pragma once

namespace Game
{
	class Animal : public Organism
	{
	public:
		Animal(World* w) : Organism(w) {}

		void action() override;
		void collision(Organism* target, bool isAttacker = false) override;
	};
}
