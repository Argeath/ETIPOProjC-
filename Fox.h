#pragma once

namespace Game {
	class Fox : public Animal {
	public:

		Fox(World* w) : Animal(w) {
			appearance.sign = 'F';
			appearance.colors = COLOR_PAIR(6) | A_BOLD;
			strength = 3;
			initiative = 7;
		}

		void collision(Organism* target, bool isAttacker = false) override {
			if(isAttacker && target->strength > strength)
			{
				action();
				throw Engine::InterruptActionException();
			}

			Animal::collision(target, isAttacker);
		};

		OrganismType getType() override { return FOX; }
	};
}
