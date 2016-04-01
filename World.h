#pragma once

namespace Game {
	class World : public Engine::BaseGame
	{
		list<Organism*> organisms;

	public:
		World(Engine::Window* window) : BaseGame(window)
		{
			Wolf* wolf = new Wolf(this);
			wolf->position = V2(5, 6);
			organisms.push_back(wolf);
		}

		void update(double deltaTime) override;
		void render() override;
	};
}
