#pragma once

namespace Game {
	class Turtle : public Animal {
	public:

		Turtle(World* w) : Animal(w) {
			appearance.sign = 'T';
			appearance.colors = COLOR_PAIR(7);
			strength = 2;
			initiative = 1;
		}

		void collision(Organism* target, bool isAttacker = false) override {
			if (target->strength < 5)
				throw Engine::InterruptActionException();

			Animal::collision(target, isAttacker);
		};

		OrganismType getType() override { return TURTLE; }
	};
}
