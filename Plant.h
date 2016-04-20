#pragma once

namespace Game
{
	class Plant : public Organism
	{
	public:
		Plant(World* w) : Organism(w) {}

		void action() override;
		void collision(Organism* target, bool isAttacker = false) override {};
	};
}