#pragma once

namespace Game {
	class Wolf : public Organism
	{
	public:

		Wolf(World* w) : Organism(w) {
			sign = 'W';
			strength = 9;
			initiative = 5;
		}

		void action() override;
		void collision() override;
	};
}
