#pragma once

namespace Game {
	class World;

	class Organism {
	public:
		virtual ~Organism() {}

		Organism(World* w) : strength(0), initiative(0), sign('x'), world(w) {}

		int strength;
		int initiative;
		Utils::Vector2<int> position;
		char sign;

		virtual void action() = 0;
		virtual void collision() = 0;
		void draw();
	protected:
		World* world;

	};
}
