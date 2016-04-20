#pragma once

namespace Game {
	class Antelope : public Animal {
	public:

		Antelope(World* w) : Animal(w) {
			appearance.sign = 'A';
			appearance.colors = COLOR_PAIR(9) | A_BOLD;
			strength = 4;
			initiative = 4;
		}

		void action() override {
			Animal::action();
			Animal::action();
		}

		void collision(Organism* target, bool isAttacker = false) override {
			Animal::collision(target, isAttacker);
		}

		OrganismType getType() override { return ANTELOPE; }
	};
}
