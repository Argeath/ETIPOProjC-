#pragma once

namespace Game
{
	class Wolfberry : public Plant
	{
	public:
		Wolfberry(World* w) : Plant(w) {
			appearance.sign = 'W';
			appearance.colors = COLOR_PAIR(4) | A_BOLD;
			strength = 99;
		}

		void collision(Organism*, bool isAttacker = false) override {
			isDieing = true;
		}
		OrganismType getType() override { return WOLFBERRY; }
	};
}