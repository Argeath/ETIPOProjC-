#pragma once

namespace Game
{
	class Wolfberry : public Plant
	{
	public:
		Wolfberry(World* w) : Plant(w) {
			appearance.sign = 'W';
			appearance.colors = COLOR_PAIR(4) | A_BOLD;
			strength = 999;
		}

		void collision(Organism* target, bool isAttacker = false) override {
			target->isDieing = true;
			isDieing = true;
		}
		OrganismType getType() override { return WOLFBERRY; }
	};
}